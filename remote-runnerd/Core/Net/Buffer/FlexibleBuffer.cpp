/**
 @file FlexibleBuffer.cpp
 @date 19.03.15

 @author Daniil A Megrabyan
*/

#include "FlexibleBuffer.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	FlexibleBuffer::FlexibleBuffer()
	{
		// Тесновато, но это пока :)
		_vector.resize(0, 0);

		// Буфер пустой - начало == конец
		setg(_vector.data(), _vector.data(), _vector.data());
		setp(_vector.data(), _vector.data());
	}
	
	std::basic_streambuf<char>::int_type FlexibleBuffer::overflow(std::basic_streambuf<char>::int_type c)
	{
		if (c == EOF) {
			return AbstractBuffer::overflow(c);
		}
		
		_vector.push_back(c);
		
		setp(_vector.data(), _vector.data() + _vector.size());
		pbump(_vector.size());
		
		return c;
	}

	std::streamsize FlexibleBuffer::xsputn(const char_type* sequence, std::streamsize count)
	{
		if (_complete) {
			return false;
		}
			
		// Увеличиваем буфер
		resize(getSize() + count);
		
		// Поглощаем новые данные
		std::size_t retval = AbstractBuffer::xsputn(sequence, count);

		return retval;
	}
	
	void FlexibleBuffer::preserve()
	{
		_complete = true;
	}
} } } }
