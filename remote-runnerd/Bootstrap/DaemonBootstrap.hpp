/**
 @file DaemonBootstrap.hpp
 @date 02.07.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_DaemonBootstrap_hpp
#define DrWeb_RemoteRunner_Core_DaemonBootstrap_hpp

#include "../AbstractBootstrap.hpp"

namespace DrWeb { namespace RemoteRunner {
	class DaemonBootstrap : public AbstractBootstrap
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Aliases */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		DaemonBootstrap(const std::string name, std::fstream& configuration_stream, std::ostream& out_stream, std::ostream& error_stream);
		virtual ~DaemonBootstrap();
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		/// Системные события
		std::ofstream _systemlog_stream;
		
		/// Сетевые события
		std::ofstream _netlog_stream;
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
		virtual bool run() override;
	/** @} */

	/** @name Getters */
	/** @{ */
	public:
	/** @} */
	};
} }

#endif
