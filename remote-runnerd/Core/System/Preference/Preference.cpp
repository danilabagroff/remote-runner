/**
 @file Preference.cpp
 @date 11.06.15

 @author Daniil A Megrabyan
*/

#include "Preference.hpp"

#include "../../../Build.hpp"
#include "../../LogLevel.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	Preference::Preference()
	:
		AbstractPreference(
							"core",
							{
								{"TelnetServer", std::ref(_telnetserver_socket_address)},
								
								{"SystemLogLevel", std::ref(_system_loglevel)},
								{"NetLogLevel", std::ref(_net_loglevel)},
											
								{"SystemLogFile", std::ref(_system_logfile)},
								{"NetLogFile", std::ref(_net_logfile)},
											
								{"SystemLogOutput", std::ref(_system_logoutput)},
								{"NetLogOutput", std::ref(_net_logoutput)},
								
								{"ApplicationListFile", std::ref(_applicationlist_cfgfile)},
								{"ApplicationTimeout", std::ref(_application_timeout)}
							}
		),
		_telnetserver_socket_address(Build::TelnetServerURI),
	
		_system_loglevel(LogLevel::Error),
		_net_loglevel(LogLevel::Error),
	
		_system_logfile("system.log"),
		_net_logfile("net.log"),
	
		_system_logoutput(true),
		_net_logoutput(false),
	
		_applicationlist_cfgfile(Build::ApplicationListFile),
		_application_timeout(Build::ApplicationTimeout)
	{
		
	}
	
	const SocketAddressOption& Preference::getTelnetServerSocketAddress() const
	{
		return _telnetserver_socket_address;
	}
	
	const LogLevelOption& Preference::getSystemLogLevel() const
	{
		return _system_loglevel;
	}
	
	const LogLevelOption& Preference::getNetLogLevel() const
	{
		return _net_loglevel;
	}
	
	const FilePathOption& Preference::getSystemLogFile() const
	{
		return _system_logfile;
	}
	
	const FilePathOption& Preference::getNetLogFile() const
	{
		return _net_logfile;
	}
	
	const SwitchOption& Preference::getSystemLogOutput() const
	{
		return _system_logoutput;
	}
	
	const SwitchOption& Preference::getNetLogOutput() const
	{
		return _net_logoutput;
	}
	
	const FilePathOption& Preference::getApplicationListFile() const
	{
		return _applicationlist_cfgfile;
	}
	
	const TimeoutOption& Preference::getApplicationTimeout() const
	{
		return _application_timeout;
	}
} } } }
