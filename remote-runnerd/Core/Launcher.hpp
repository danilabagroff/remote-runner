/**
 @file Launcher.hpp
 @date 11.06.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_Launcher_hpp
#define DrWeb_RemoteRunner_Core_Launcher_hpp

#include "Net/Connection.hpp"

#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <mutex>
#include <set>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class Launcher
	{
	/** @name Constructors */
	/** @{ */
	public:
		Launcher(std::string filepath, unsigned long timeout);
		virtual ~Launcher();
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		const std::string _filepath;
		const std::chrono::seconds _timeout;

		std::set<std::string> _access_set;
		mutable std::mutex _mutex;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		bool reload();
		bool exec(const std::string command, std::weak_ptr<Net::Connection> connection);
	/** @} */
		
	/** @name Converters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool isAllowed(const std::string& command) const;
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
	/** @} */
	};
} } }

#endif
