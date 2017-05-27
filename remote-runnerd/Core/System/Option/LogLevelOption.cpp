/**
 @file LogLevelOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "LogLevelOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	LogLevelOption::LogLevelOption(LogLevel level)
	:
		_level(level)
	{
		
	}
	
	bool LogLevelOption::operator()(std::istream& stream)
	{
		std::string level;
		stream >> level;
		
		if (level.compare("debug") == 0) {
			_level = LogLevel::Debug;
		} else if (level.compare("fatal") == 0) {
			_level = LogLevel::Fatal;
		} else if (level.compare("error") == 0) {
			_level = LogLevel::Error;
		} else if (level.compare("warning") == 0) {
			_level = LogLevel::Warning;
		} else if (level.compare("notice") == 0) {
			_level = LogLevel::Notice;
		} else if (level.compare("none") == 0) {
			_level = LogLevel::None;
		} else {
			return false;
		}		

		return true;
	}
	
	const LogLevel& LogLevelOption::getLevel() const
	{
		return _level;
	}
} } } }
