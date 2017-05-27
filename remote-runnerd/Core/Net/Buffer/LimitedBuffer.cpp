/**
 @file LimitedBuffer.cpp
 @date 10.03.15

 @author Daniil A Megrabyan
*/

#include "LimitedBuffer.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	LimitedBuffer::LimitedBuffer(const std::size_t limit)
	{
		// Устаналиваем фиксированный размер буфера
		_vector.resize(limit, 0);

		// Размечаем области

		// get = чтение в = ввод в
		setg(_vector.data(), _vector.data(), _vector.data() + _vector.size());
		
		// put = запись сюда = вывод сюда
		setp(_vector.data(), _vector.data() + _vector.size());
	}
	
	std::streamsize LimitedBuffer::xsputn(const char_type* sequence, std::streamsize count)
	{
		// Поглощаем только нужное(retval) количество данных
		const std::size_t retval = AbstractBuffer::xsputn(sequence, count);
		
		// Получены все необходимые данные?
		_complete = (epptr() == pptr());
		
		return retval;
	}
} } } }
