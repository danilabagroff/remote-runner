/**
 @file AbstractLog.hpp
 @date 24.02.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_AbstractLog_hpp
#define DrWeb_RemoteRunner_Core_AbstractLog_hpp

#include <future>

#include "LogRegister.hpp"
#include "../Wand/WorkerThread.hpp"

#include <map>
#include <iostream>
#include <forward_list>
#include <functional>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class AbstractLog
	{
	/** @name Constants */
	/** @{ */
	public:
		static const std::map<LogLevel, std::string> LevelMap;
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractLog(const std::string prefix)
		:
			_prefix(prefix)
		{
			
		};
		
		virtual ~AbstractLog()
		{
			
		};
	/** @} */

	/** @name Properties */
	/** @{ */
	private:
		std::forward_list<std::reference_wrapper<std::ostream>> _list;
		const std::string _prefix;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual void pre(const LogLevel& level, const std::thread::id& thread_id)
		{
			/// @bug Время журналирования, а не фактического выполнения!
			std::time_t raw_time = std::time(nullptr);
			char formatted_time[20];
			std::strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", std::localtime(&raw_time));

			operator()(AbstractLog::LevelMap.at(level), " [", formatted_time, "] ", thread_id, "\\", _prefix, "\\");
		};
		
		void clear()
		{
			_list.clear();
		};
		
		void add(std::ostream& stream)
		{
			_list.push_front(stream);
		};
		
		void remove(std::ostream& stream)
		{
			/// @todo
			// _list.remove(stream);
		};
	/** @} */

	/** @name Getters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
		template<class... Args>
		void operator()(const LogLevel level, const std::thread::id thread_id, const Args&... args)
		{
			pre(level, thread_id);
			operator()(args...);
			for (std::ostream& stream : _list) {
				stream << std::endl;
			}
		}
		
		template<typename A, typename... Args>
		void operator()(A arg, const Args&... args)
		{
			for (std::ostream& stream : _list) {
				stream << arg;
			}
			operator()(args...);
		}
		
		inline void operator()()
		{

		}
	/** @} */
	};	
} } }

#endif
