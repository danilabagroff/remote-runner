/**
 @file Log.hpp
 @date 20.02.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Log_hpp
#define DrWeb_RemoteRunner_Core_Net_Log_hpp

#include "../AbstractLog.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class Log : public AbstractLog
	{
	/** @name Constructors */
	/** @{ */
	public:
		Log()
		:
			AbstractLog("Net")
		{
			
		}
		virtual ~Log() = default;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual void pre(const LogLevel& level, const std::thread::id& thread_id) override
		{
			AbstractLog::pre(level, thread_id);
		};
	/** @} */
	};
} } } }

#endif
