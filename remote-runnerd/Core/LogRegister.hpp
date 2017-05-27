/**
 @file LogRegister.hpp
 @date 20.02.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_LogRegister_hpp
#define DrWeb_RemoteRunner_Core_LogRegister_hpp

#include "LogLevel.hpp"

#include "../Wand/WorkerThread.hpp"
#include <iostream>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	template <typename L>
	class LogRegister
	{
	/** @name Constructors */
	/** @{ */
	private:
		LogRegister()
		:
			_level(LogLevel::Error)
		{
			
		};
		
		virtual ~LogRegister() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
		static LogRegister<L>& Instance()
		{
			static LogRegister<L> instance;
			
			return instance;
		}
		
		static std::shared_ptr<wand::worker_thread> Registrar(std::shared_ptr<wand::worker_thread> registrar = nullptr)
		{
			static std::shared_ptr<wand::worker_thread> worker((registrar != nullptr) ? registrar : wand::dummy_thread::instance());
/*
			if (nullptr != registrar) {
				worker = registrar;
			}
*/
			return worker;
		}
	/** @} */

	/** @name Properties */
	/** @{ */
	private:
		LogLevel _level;
		L _log;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
		bool setLevel(const LogLevel level)
		{
			_level = level;
			
			return (level > LogLevel::None);
		};
		
		void addStream(std::ostream& stream)
		{
			_log.add(stream);
		};
		
		void removeStream(std::ostream& stream)
		{
			_log.remove(stream);
		};
		
		void removeAllStreams()
		{
			_log.clear();
		};
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const LogLevel& getLevel() const
		{
			return _level;
		};
	/** @} */

	/** @name Templates */
	/** @{ */
	public:
		template<class... Args>
		static void Log(const LogLevel level, const Args&... args)
		{
			std::thread::id thread_id(std::this_thread::get_id());
			LogRegister<L>::Registrar()->send([=]()
							{
								LogRegister<L>& instance(LogRegister<L>::Instance());
								if (instance.getLevel() >= level) {
									instance._log(level, thread_id, args...);
								}
							});
		}
		
		template<class... Args>
		static void Fatal(const Args&... args)
		{
			Log(LogLevel::Fatal, args...);
		}
		
		template<class... Args>
		static void Error(const Args&... args)
		{
			Log(LogLevel::Error, args...);
		}
		
		template<class... Args>
		static void Warning(const Args&... args)
		{
			Log(LogLevel::Warning, args...);
		}
		
		template<class... Args>
		static void Notice(const Args&... args)
		{
			Log(LogLevel::Notice, args...);
		}
		
		template<class... Args>
		static void Debug(const Args&... args)
		{
			Log(LogLevel::Debug, args...);
		}
	/** @} */
	};
} } }

#endif
