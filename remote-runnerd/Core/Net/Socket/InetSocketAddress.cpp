/**
 @file InetSocketAddress.cpp
 @date 08.03.15

 @author Daniil A Megrabyan
*/

#include "InetSocketAddress.hpp"

#include <arpa/inet.h>
#include <netdb.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	InetSocketAddress::InetSocketAddress(const std::string host, const unsigned short port)
	{
		bzero(&_address, sizeof(_address));
/*
		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = (host.compare("0.0.0.0") != 0) ? htonl(INADDR_ANY) : inet_addr(host.c_str());
		_address.sin_port = htons(port);
*/
		
		struct addrinfo hint, *resolv;
		
		bzero(&hint, sizeof(addrinfo));
		hint.ai_flags = (host.compare("0.0.0.0") == 0) ? AI_PASSIVE : AI_CANONNAME;
		hint.ai_family = AF_INET;
		
		if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hint, &resolv) != 0) {
			return ;
		}

		/// @xxx Может быть так, что из n-resolved адресов рабочий будет далеко не первый в связаном списке resolv
		if (resolv->ai_family == AF_INET) {
			memcpy(&_address, resolv->ai_addr, sizeof(sockaddr_in));
		}
		
		if (NULL != resolv) {
			freeaddrinfo(resolv);
		}
		
		
	}

	InetSocketAddress::InetSocketAddress(const unsigned short port)
	{
		bzero(&_address, sizeof(_address));

		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = htonl(INADDR_ANY);
		_address.sin_port = htons(port);
	}
	
	InetSocketAddress::InetSocketAddress()
	{
		bzero(&_address, sizeof(_address));
		_address.sin_family = AF_INET;
	}
	
	const std::string InetSocketAddress::getHost()
	{
		char buffer[INET_ADDRSTRLEN];
		
		return std::string(inet_ntop(AF_INET, &_address.sin_addr, buffer, sizeof(buffer)));
	}
	
	const unsigned short InetSocketAddress::getPort()
	{
		return ntohs(_address.sin_port);
	}
	
	struct sockaddr* InetSocketAddress::getPointer()
	{
		return (struct sockaddr*)&_address;
	}
	
	const SocketFamily InetSocketAddress::getFamily()
	{
		return SocketFamily::Inet;
	}
	
	const socklen_t InetSocketAddress::getSize()
	{
		return sizeof(_address);
	}
} } } }
