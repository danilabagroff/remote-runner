/**
 @file Build.cpp
 @date 02.07.15
 @author Daniil A Megrabyan
 */

#include "Build.hpp"

namespace DrWeb { namespace RemoteRunner {
	
#ifdef DRWEB_REMOTERUNNER_CONFIG_FILE
	const std::string Build::ConfigurationFile = DRWEB_REMOTERUNNER_CONFIG_FILE;
#else
	const std::string Build::ConfigurationFile = "/etc/remote-runnerd.conf";
#endif
	
#ifdef DRWEB_REMOTERUNNER_TELNET_SERVER_URI
	const std::string Build::TelnetServerURI = DRWEB_REMOTERUNNER_TELNET_SERVER_URI;
#else
	const std::string Build::TelnetServerURI = "tcp://localhost:12345";
#endif
	
#ifdef DRWEB_REMOTERUNNER_DAEMON_PID_FILE
	const std::string Build::DaemonPIDFile = DRWEB_REMOTERUNNER_DAEMON_PID_FILE;
#else
	const std::string Build::DaemonPIDFile = "/var/run/remote-runnerd.pid";
#endif
	
#ifdef DRWEB_REMOTERUNNER_APPLICATION_LIST_FILE
	const std::string Build::ApplicationListFile = DRWEB_REMOTERUNNER_APPLICATION_LIST_FILE;
#else
	const std::string Build::ApplicationListFile = "/etc/remote-runnerd.app.list";
#endif
	
#ifdef DRWEB_REMOTERUNNER_APPLICATION_TIMEOUT
	const unsigned long Build::ApplicationTimeout = DRWEB_REMOTERUNNER_APPLICATION_TIMEOUT;
#else
	const unsigned long Build::ApplicationTimeout = 30;
#endif
	
} }
