/**
 @file AbstractBuffer.cpp
 @date 11.03.15

 @author Daniil A Megrabyan
*/

#include "AbstractBuffer.hpp"

#include "Log.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	AbstractBuffer::AbstractBuffer()
	:
		_complete(false)
	{
		setg(_vector.data(), _vector.data(), _vector.data() + _vector.size());
		setp(_vector.data(), _vector.data() + _vector.size());
	}

	std::streamsize AbstractBuffer::absorb(AbstractBuffer& source)
	{
		// Предлагаем откопировать все из источника. В итоге, в useful_data — количество данных, которое реально пригодилось
		std::streamsize useful_data = sputn(source.gptr(), source.egptr() - source.gptr());
		
		// Удаляем(FIFO) из источника то количество данных, которое пригодилось целевому(this) буферу
		source._vector.erase(source._vector.begin(), source._vector.begin() + useful_data);

		// Запоминаем положение вводного/get курсора
		std::streamsize get_offset(source.egptr() - source.gptr());
		
		// Устанавливаем ввводные/get указатели источника "начало" и "конец" в соответствии с обрезанным буфером
		source.setg(source._vector.data(), source._vector.data() + (useful_data > get_offset ? 0 : useful_data - get_offset), source._vector.data() + source._vector.size());
		
		// Запоминаем положение выводного/put курсора
		std::streamsize put_offset(source.epptr() - source.pptr());
		
		// Устанавливаем выводные/put указатели источника "начало" и "конец" в соответствии с обрезанным буфером
		source.setp(source._vector.data(), source._vector.data() + source._vector.size());
		
		// Двигаем выводной/put курсор источника на прежнее место или остаемся в начале
		source.pbump(useful_data > put_offset ? 0 : useful_data - put_offset);
		
		return useful_data;
		
	}
	
	std::streamsize AbstractBuffer::xsputn(const char_type* sequence, std::streamsize count)
	{
		// Если буфер уже не требует данных, то ничего не копируем
		if (_complete) {
			return 0;
		}

		// Оставшееся место в буфере
		std::streamsize reserve = epptr() - pptr();
		
		// Копируем только то, что влезает
		std::size_t retval = (count <= reserve ? count : reserve);
		
		// Копируем из последовательности символов учитывая текущее положение курсора		
		std::copy(sequence, sequence + retval, _vector.data() + (pptr() - pbase()));

		// Двигаем курсор на количество откопированных байт
		pbump(static_cast<int>(retval));

		return retval;
	}

	std::basic_streambuf<char>::int_type AbstractBuffer::overflow(std::basic_streambuf<char>::int_type c)
	{
		return basic_streambuf<char>::overflow(c);
	}
	
	void AbstractBuffer::resize(const std::size_t size)
	{
		// Запоминаем количество данных, которыми был заполнен буфер
		std::streamsize used_data = pptr() - pbase();
	
		// Изменяем размер хранилища
		_vector.resize(size, 0);
		
		// Устанавливаем новую метку-указатель конца выводного буфера на основании нового размера хранилища
		setp(_vector.data(), _vector.data() + _vector.size());
		
		// Уменьшен(if) или увелинчен(else) буфер?
		if (used_data > _vector.size()) {
			// Двигаем выводной/put курсор в конец, т.к. буфер стал меньше
			pbump(static_cast<int>(_vector.size()));

			// устаналиваем указатель курсора в конец, иначе — восстанавливаем предыдущее положение
			setg(_vector.data(), (gptr() - eback() >= _vector.size()) ? _vector.data() + _vector.size() : _vector.data() + (gptr() - eback()), _vector.data() + _vector.size());
			_vector.shrink_to_fit();
		} else {
			// Если буфер стал больше, то восстанавливаем положение выводного курсора в исходное — до ресайза
			setg(_vector.data(), _vector.data() + (gptr() != NULL ? gptr() - eback() : 0), _vector.data() + _vector.size());

			pbump(static_cast<int>(used_data));
		}
	}
	
	std::basic_streambuf<char>::pos_type AbstractBuffer::seekoff(std::basic_streambuf<char>::off_type offset, std::ios_base::seekdir direction, std::ios_base::openmode mode)
	{
		switch (direction) {
			case std::ios_base::seek_dir::beg:
				if (mode == std::ios_base::in) {
					if (eback() + offset > egptr()) {
						return pos_type(off_type(-1));
					}
					setg(eback(), eback() + offset, egptr());
				}
				
				if (mode == std::ios_base::out) {
					if (pbase() + offset > epptr()) {
						return pos_type(off_type(-1));
					}
					/// @todo
					// pbump();
				}
				break;
			case std::ios_base::seek_dir::end:
				if (mode == std::ios_base::in) {
					if (egptr() + offset > egptr()) {
						return pos_type(off_type(-1));
					}
					setg(eback(), egptr() + offset, egptr());
				}
				
				if (mode == std::ios_base::out) {
					if (epptr() + offset > epptr()) {
						return pos_type(off_type(-1));
					}
					/// @todo
					// pbump();
				}
				break;
			case std::ios_base::seek_dir::cur:
				if (mode & std::ios_base::in && mode & std::ios_base::out) {
					return pos_type(off_type(-1));
				}
				
				if (mode == std::ios_base::in) {
					if (gptr() + offset > egptr()) {
						return pos_type(off_type(-1));
					}
					setg(eback(), gptr() + offset, egptr());
				}
				
				if (mode == std::ios_base::out) {
					if (pptr() + offset > epptr()) {
						return pos_type(off_type(-1));
					}
					pbump(offset);
				}
				break;
				
			default:
				return pos_type(off_type(-1));
				break;
		}
		
		return gptr() - eback();
	}
	
	std::basic_streambuf<char>::pos_type AbstractBuffer::seekpos(std::basic_streambuf<char>::pos_type position, std::ios_base::openmode mode)
	{
		//  using an absolute streampos position
		return seekoff(off_type(position), std::ios_base::beg, mode);
	}
	
	const std::size_t AbstractBuffer::getSize() const
	{
		return _vector.size();
	}
	
	const std::vector<std::basic_streambuf<char>::char_type>& AbstractBuffer::getVector() const
	{
		return _vector;
	}
	
	const bool AbstractBuffer::isEmpty()
	{
		return getSize() <= 0;
	}
	
	const bool AbstractBuffer::isComplete() const
	{
		return _complete;
	}
} } } }
