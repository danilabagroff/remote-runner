/**
 @file AbstractInputStream.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractInputStream.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	AbstractInputStream::AbstractInputStream(std::istream& stream)
	:
		_stream(stream)
	{
		std::streampos restore = _stream.tellg();
		_stream.seekg(0, std::ios::end);
		_length = _stream.tellg();
		_stream.seekg(restore);
	}
	
	const unsigned char AbstractInputStream::readByte()
	{
		if (!_stream.good()) {
			throw (ExceptionProvoker<StreamException>() << StreamException::Code::StreamReading << "Buffer underrun at needle position: " << _stream.tellg() << " while requesting length: 1");
		}
		
		return _stream.get();
	}
	
	const std::string AbstractInputStream::readBytes(const long length)
	{
		if (!_stream.good()) {
			throw (ExceptionProvoker<StreamException>() << StreamException::Code::StreamReading << "Buffer underrun at needle position: " << _stream.tellg() << " while requesting length: " << length);
		}
		
		char* buffer = new char[length];
		/// @bug Возможная утечка памяти если во время read() произошел Exception
		_stream.read(buffer, length);
		std::string retval(buffer, length);
		delete[] buffer;
		
		return retval;
	}
	
	const std::uint8_t AbstractInputStream::readMarker()
	{
		return readByte();
	}
	
	std::istream& AbstractInputStream::getStream()
	{
		return _stream;
	}
	
	const std::size_t AbstractInputStream::getPosition() const
	{
		return _stream.tellg();
	}
	
	void AbstractInputStream::operator>>(std::uint8_t& value)
	{
		value =	readByte();
	}
} } }
