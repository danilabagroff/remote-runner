/**
 @file ClientSocket.cpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#include "ClientSocket.hpp"

#include "InetSocketAddress.hpp"
#include "UnixSocketAddress.hpp"

#include "../Log.hpp"
#include "../../../Wand/MakeUnique.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	ClientSocket::ClientSocket(std::unique_ptr<AbstractSocketAddress> address, const int server_handle)
	:
		AbstractSocket(std::move(address))
	{
		socklen_t length = _address->getSize();
		if (server_handle > 0) {
			_handle = ::accept(server_handle, _address->getPointer(), &length);
			if (_handle > 0) {
				LogRegister<Net::Log>::Notice("ClientSocket(", _handle, ") > Accepted");
			}
		}
	}
	
	bool ClientSocket::init()
	{
		if (!AbstractSocket::init()) {
			return false;
		}
	
		if (connect(_handle, _address->getPointer(), _address->getSize()) == -1) {
			_handle = 0;
			_last_error = errno;
			return false;
		}
		
		return true;
	}
} } } }
