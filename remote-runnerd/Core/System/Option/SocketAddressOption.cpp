/**
 @file SocketAddressOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "SocketAddressOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	SocketAddressOption::SocketAddressOption(const std::string& host, unsigned short port)
	:
		URIOption("tcp://" + host + ":" + std::to_string(port))
	{
		
	}
	
	SocketAddressOption::SocketAddressOption(const std::string& socket_file)
	:
		URIOption("unix://" + socket_file)
	{
		
	}
	
	SocketAddressOption::SocketAddressOption(const wand::uri& uri)
	:
		URIOption(uri)
	{
		
	}
	
	
	bool SocketAddressOption::operator()(std::istream& stream)
	{
		if (!URIOption::operator()(stream)) {
			return false;
		}
		
		return parse();
	}
	
	bool SocketAddressOption::parse()
	{
		if (getScheme().compare("tcp") == 0) {
			_family = SocketAddressOption::SocketFamily::TCP;
		} else if (getScheme().compare("unix") == 0) {
			_family = SocketAddressOption::SocketFamily::Unix;
		} else {
			_family = SocketAddressOption::SocketFamily::Unknown;
			return false;
		}
		
		return true;
	}
	
	const SocketAddressOption::SocketFamily SocketAddressOption::getFamily() const
	{
		return _family;
	}
} } } }
