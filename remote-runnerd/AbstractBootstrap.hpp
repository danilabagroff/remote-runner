/**
 @file AbstractBootstrap.hpp
 @date 02.07.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_AbstractBootstrap_hpp
#define DrWeb_RemoteRunner_AbstractBootstrap_hpp

#include "Configuration.hpp"

#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <syslog.h>

namespace DrWeb { namespace RemoteRunner {
	class AbstractBootstrap
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractBootstrap(const std::string name, std::fstream& configuration_stream);
		virtual ~AbstractBootstrap();
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
		const std::string _name;
		Configuration _configuration;
	/** @} */

	/** @name Factories */
	/** @{ */
	public:
	/** @} */

	/** @name Operators  */
	/** @{ */
	public:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool run() = 0;
		
	protected:
		bool boot(bool load_preference = true);
	/** @} */

	/** @name Getters */
	/** @{ */
	public:
		const std::string& getName() const;
		
	protected:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
	/** @} */
	};
} }

#endif
