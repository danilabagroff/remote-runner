/**
 @file ServerSocket.cpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#include "ServerSocket.hpp"

#include "InetSocketAddress.hpp"
#include "UnixSocketAddress.hpp"

#include "../../../Wand/MakeUnique.hpp"
#include <string.h>
#include <arpa/inet.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	ServerSocket::ServerSocket(std::unique_ptr<AbstractSocketAddress> address)
	:
		AbstractSocket(std::move(address))
	{
		
	}
	
	bool ServerSocket::init()
	{
		if (!AbstractSocket::init()) {
			return false;
		}
		
		int yes = 1;
		
		if (setsockopt(_handle, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			_last_error = errno;
			return false;
		}
		
		if (bind(_handle, _address->getPointer(), _address->getSize()) == -1) {
			_last_error = errno;
			return false;
		}
		
		if (listen(_handle, 10) == -1) {
			_last_error = errno;			
			return false;
		}
		
		return true;
	}
	
	std::unique_ptr<ClientSocket> ServerSocket::accept() const
	{
		switch (_address->getFamily()) {
			case SocketFamily::Inet:
				return wand::make_unique<ClientSocket>(wand::make_unique<InetSocketAddress>(), _handle);
			case SocketFamily::Local:
				return wand::make_unique<ClientSocket>(wand::make_unique<UnixSocketAddress>("/dev/null"), _handle);
			default:
				return nullptr;
		}
	}
} } } }
