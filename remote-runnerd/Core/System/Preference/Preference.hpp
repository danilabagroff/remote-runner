/**
 @file Preference.hpp
 @date 11.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Preference_hpp
#define DrWeb_RemoteRunner_Core_System_Preference_hpp

#include "../AbstractPreference.hpp"

#include "../Option/SocketAddressOption.hpp"
#include "../Option/FilePathOption.hpp"
#include "../Option/LogLevelOption.hpp"
#include "../Option/SwitchOption.hpp"
#include "../Option/TimeoutOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class Preference final : public System::AbstractPreference
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		Preference();
		virtual ~Preference() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		SocketAddressOption _telnetserver_socket_address;
		
		LogLevelOption _system_loglevel;
		LogLevelOption _net_loglevel;
		
		FilePathOption _system_logfile;
		FilePathOption _net_logfile;
		
		SwitchOption _system_logoutput;
		SwitchOption _net_logoutput;

		FilePathOption _applicationlist_cfgfile;
		TimeoutOption _application_timeout;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
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
		const Core::System::SocketAddressOption& getTelnetServerSocketAddress() const;
		
		const Core::System::LogLevelOption& getSystemLogLevel() const;
		const Core::System::LogLevelOption& getNetLogLevel() const;
		
		const Core::System::FilePathOption& getSystemLogFile() const;
		const Core::System::FilePathOption& getNetLogFile() const;
		
		const Core::System::SwitchOption& getSystemLogOutput() const;
		const Core::System::SwitchOption& getNetLogOutput() const;
		
		const FilePathOption& getApplicationListFile() const;
		const TimeoutOption& getApplicationTimeout() const;
	/** @} */

	/** @name States */
	/** @{ */
	public:
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
} } } }

#endif
