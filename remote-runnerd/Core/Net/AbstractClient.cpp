/**
 @file AbstractClient.cpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#include "AbstractClient.hpp"

#include "Log.hpp"
#include <array>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	const std::size_t AbstractClient::Batch = 4048;
	
	AbstractClient::AbstractClient(std::unique_ptr<ClientSocket> socket)
	:
		_socket(std::move(socket))
	{
		_socket->init();
	}
	
	AbstractClient::~AbstractClient()
	{
		
	}
	
	const int AbstractClient::getSocketHandle()
	{
		return _socket->getHandle();
	}
} } } }
