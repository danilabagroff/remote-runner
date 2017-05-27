/**
 @file SocketError.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#include "SocketError.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	SocketError::SocketError(const std::string message)
	:
		_message(message)
	{
		
	}
	
	const std::string SocketError::getAlias() const
	{
		return "SocketError";
	}
	
	const std::string& SocketError::getMessage() const
	{
		return _message;
	}
} } } }
