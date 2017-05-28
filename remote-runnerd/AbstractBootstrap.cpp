/**
 @file AbstractBootstrap.cpp
 @date 02.07.15

 @author Daniil A Megrabyan
*/

#include "AbstractBootstrap.hpp"

#include "Build.hpp"

namespace DrWeb { namespace RemoteRunner {
	AbstractBootstrap::AbstractBootstrap(const std::string name, std::fstream& configuration_stream)
	:
		_name(name),
		_configuration(configuration_stream)
	{
	}
	
	AbstractBootstrap::~AbstractBootstrap()
	{

	}
	
	bool AbstractBootstrap::boot(bool load_preference)
	{
		if (!_configuration.isOpened() && load_preference) {
			if (!_configuration.open(Build::ConfigurationFile)) {
				syslog(LOG_ERR, "Configuration file does not exist or access is denied");
				
				return false;
			}
		}
		
		return true;
	}	
	
	const std::string& AbstractBootstrap::getName() const
	{
		return _name;
	}
} }
