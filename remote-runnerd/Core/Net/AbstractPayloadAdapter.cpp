/**
 @file AbstractPayload.cpp
 @date 13.03.15

 @author Daniil A Megrabyan
*/

#include "AbstractPayloadAdapter.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	AbstractPayloadAdapter::AbstractPayloadAdapter()
	:
		_stream(NULL)
	{

	}
	
	bool AbstractPayloadAdapter::init()
	{
		if (nullptr == _buffer) {
			return false;
		}

		_stream.rdbuf(_buffer.get());
		return true;
	}
	
	bool AbstractPayloadAdapter::absorb(FlexibleBuffer& buffer)
	{
		/// @note Если адаптер полезной нагрузки почему-то забыл создать принимающий буфер — абсорбировать ему нечем = данные ему не нужны
		/// @note Запускать ли без буфера/данных digest()
		if (_buffer == nullptr) {
			return true;
		}
		
		_buffer->absorb(buffer);

		if (_buffer->isComplete()) {
			digest();
			
			return true;
		}
		
		return false;
	}
} } } }
