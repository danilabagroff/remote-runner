/**
 @file AbstractLog.cpp
 @date 24.02.15

 @author Daniil A Megrabyan
*/

#include "AbstractLog.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	const std::map<LogLevel, std::string> AbstractLog::LevelMap = {
		{LogLevel::Fatal, "[X]"},
		{LogLevel::Error, "[E]"},
		{LogLevel::Warning, "[W]"},
		{LogLevel::Notice, "[I]"},
		{LogLevel::Debug, "[D]"}
	};	
} } }
