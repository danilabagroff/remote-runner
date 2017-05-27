/**
 @file Build.hpp
 @date 02.07.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Build_hpp
#define DrWeb_RemoteRunner_Build_hpp

#include <string>

namespace DrWeb { namespace RemoteRunner {
	class Build final
	{
	/** @name Constants */
	/** @{ */
	public:
		static const std::string ConfigurationFile;
		static const std::string DaemonPIDFile;
		static const std::string TelnetServerURI;
		static const std::string ApplicationListFile;
		static const unsigned long ApplicationTimeout;
	/** @} */
		
	/** @name Aliases */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		Build() = default;
		virtual ~Build() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
	/** @} */

	/** @name Factories */
	/** @{ */
	public:
	/** @} */

	/** @name Procedures  */
	/** @{ */
	public:
	/** @} */

	/** @name Getters */
	/** @{ */
	public:
	/** @} */
	};
} }

#endif
