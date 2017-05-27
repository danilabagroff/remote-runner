/**
 @file SocketRead.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#include "SocketRead.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	SocketRead::SocketRead(const std::size_t bytes)
	:
		_bytes(bytes)
	{
		
	}
	
	const std::string SocketRead::getAlias() const
	{
		return "SocketRead";
	}
	
	const std::size_t SocketRead::getBytes() const
	{
		return _bytes;
	}
} } } }
