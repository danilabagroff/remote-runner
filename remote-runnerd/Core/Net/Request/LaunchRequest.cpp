/**
 @file LaunchRequest.cpp
 @date 2017-05-26
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "LaunchRequest.hpp"

#include "PayloadAdapter/LaunchRequestCommandAdapter.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	LaunchRequest::LaunchRequest()
	:
		AbstractRequest(
						{
							std::make_shared<LaunchRequestCommandAdapter>(_command)
						}
		)
	{
		
	}
	
	void LaunchRequest::feed(std::ostream& stream)
	{
		stream << _command;
	}
	
	const std::string& LaunchRequest::getCommand() const
	{
		return _command;
	}
} } } }
