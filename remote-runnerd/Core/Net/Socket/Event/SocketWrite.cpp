/**
 @file SocketWrite.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#include "SocketWrite.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	SocketWrite::SocketWrite(const std::size_t bytes)
	:
		_bytes(bytes)
	{
		
	}
	
	const std::string SocketWrite::getAlias() const
	{
		return "SocketWrite";
	}
	
	const std::size_t SocketWrite::getBytes() const
	{
		return _bytes;
	}
} } } }
