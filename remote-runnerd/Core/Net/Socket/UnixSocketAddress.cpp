/**
 @file UnixSocketAddress.cpp
 @date 08.03.15

 @author Daniil A Megrabyan
*/

#include "UnixSocketAddress.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	UnixSocketAddress::UnixSocketAddress(const std::string path)
	{
		bzero((char *)&_address, sizeof(_address));
		/// @note Лучше strlcpy(_address.sun_path, path.c_str(), sizeof(_address.sun_path));
		strcpy(_address.sun_path, path.c_str());
		_address.sun_family = AF_UNIX;
	}
	
	void UnixSocketAddress::clear()
	{
		unlink(_address.sun_path);
	}
	
	struct sockaddr* UnixSocketAddress::getPointer()
	{
		return (struct sockaddr*)&_address;
	}
	
	const SocketFamily UnixSocketAddress::getFamily()
	{
		return SocketFamily::Local;
	}
	
	const socklen_t UnixSocketAddress::getSize()
	{
		return SUN_LEN(&_address);
	}
} } } }
