/**
 @file LogLevel.hpp
 @date 20.02.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_LogLevel_hpp
#define DrWeb_RemoteRunner_Core_LogLevel_hpp

#include <cstdint>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	/**
	 @brief Уровень журналирования
	 */
	enum class LogLevel : std::uint8_t
	{
		None = 0,
		Fatal = 10, /**< Critical Conditions/System is unusable: "socket: Failed to get a socket, exiting child/Child cannot open lock file. Exiting" */
		Error = 100, /**< Error conditions: "Premature end of script headers" */
		Warning	= 150,/**< Warning conditions: "child process 1234 did not exit, sending another SIGHUP" */
		Notice = 200,/**< Normal but significant condition: "Server seems busy, you may need to increase StartThreads" */
		Debug = 250	/**< Very-very verbose */
	};
	} } }

#endif
