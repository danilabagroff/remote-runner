/**
 @file AbstractBootstrap.cpp
 @date 02.07.15

 @author Daniil A Megrabyan
*/

#include "AbstractBootstrap.hpp"

#include "Build.hpp"

namespace DrWeb { namespace RemoteRunner {
	AbstractBootstrap::AbstractBootstrap(const std::string name, std::fstream& configuration_stream, std::ostream& out_stream, std::ostream& error_stream)
	:
		_name(name),
		_configuration(configuration_stream),
		_out_stream(out_stream),
		_error_stream(error_stream)
	{
	}
	
	AbstractBootstrap::~AbstractBootstrap()
	{

	}
	
	bool AbstractBootstrap::boot(bool load_preference)
	{
		if (!_configuration.isOpened() && load_preference) {
			if (!_configuration.open(Build::ConfigurationFile)) {
				_error_stream << getName() << ": Configuration file does not exist or access is denied" << std::endl;
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
