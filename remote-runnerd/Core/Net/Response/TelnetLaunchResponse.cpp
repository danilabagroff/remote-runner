/**
 @file TelnetLaunchResponse.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "TelnetLaunchResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	TelnetLaunchResponse::TelnetLaunchResponse(std::string output)
	:
		_output(output + "\n")
	{

	}
		
	TelnetLaunchResponse::~TelnetLaunchResponse()
	{

	}
	
	void TelnetLaunchResponse::feed(std::ostream& stream)
	{
		stream << _output;
		
		AbstractResponse::feed(stream);
	}
} } } }
