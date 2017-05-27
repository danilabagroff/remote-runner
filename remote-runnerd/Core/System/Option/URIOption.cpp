/**
 @file URIOption.cpp
 @date 26.06.15

 @author Daniil A Megrabyan
 */

#include "URIOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	URIOption::URIOption(const std::string uri)
	:
		_uri(uri)
	{

	}
	
	URIOption::URIOption(const wand::uri& uri)
	:
		_uri(uri)
	{
		
	}

	bool URIOption::operator()(std::istream& stream)
	{
		std::string uri;
		stream >> uri;

		_uri.parse(uri);

		return true;
	}

	const wand::uri& URIOption::get() const
	{
		return _uri;
	}

	const std::string& URIOption::getScheme() const
	{
		return _uri.getScheme();
	}

	const std::string& URIOption::getHost() const
	{
		return _uri.getHost();
	}
	
	const unsigned short& URIOption::getPort() const
	{
		return _uri.getPort();
	}
	
	const std::string& URIOption::getUsername() const
	{
		return _uri.getUsername();
	}

	const std::string& URIOption::getPassword() const
	{
		return _uri.getPassword();
	}

	const std::string& URIOption::getPath() const
	{
		return _uri.getPath();
	}

	const std::string& URIOption::getQuery() const
	{
		return _uri.getQuery();
	}

	const bool URIOption::hasPort() const
	{
		return (getPort() > 0);
	}
} } } }
