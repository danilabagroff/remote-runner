/**
 @file StringOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "StringOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	StringOption::StringOption(const std::string& string)
	:
		_string(string)
	{
		
	}
	
	bool StringOption::operator()(std::istream& stream)
	{
		stream >> _string;
		
		return true;
	}
	
	const std::string& StringOption::getString() const
	{
		return _string;
	}
} } } }
