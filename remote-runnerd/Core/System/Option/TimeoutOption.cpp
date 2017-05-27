/**
 @file TimeoutOption.cpp
 @date 26.06.15

 @author Daniil A Megrabyan
*/

#include "TimeoutOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	TimeoutOption::TimeoutOption(const unsigned long seconds)
	:
		_timeout(seconds)
	{

	}
	
	bool TimeoutOption::operator()(std::istream& stream)
	{
		std::string timeout;
		/// @xxx Поймать исключение и вернуть false
		stream >> timeout;

		try {
			_timeout = std::stoul(timeout);
		} catch (...) {
			_timeout = 0;
		}

		return true;
	}
	
	const unsigned long& TimeoutOption::getTimeout() const
	{
		return _timeout;
	}
} } } }
