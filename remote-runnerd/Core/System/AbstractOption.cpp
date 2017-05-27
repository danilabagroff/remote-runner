/**
 @file AbstractOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "AbstractOption.hpp"

#include <sstream>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	bool AbstractOption::operator()(const std::string& value)
	{
		std::stringstream stream(value);

		return operator()(stream);
	}
} } } }
