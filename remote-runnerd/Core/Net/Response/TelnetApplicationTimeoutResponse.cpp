/**
 @file TelnetApplicationTimeoutResponse.cpp
 @date 03.03.15

 @author Daniil A Megrabyan
*/

#include "TelnetApplicationTimeoutResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	TelnetApplicationTimeoutResponse::TelnetApplicationTimeoutResponse()
	:
		TelnetLaunchResponse("Timeout expired, application is going to be killed")
	{
	}
} } } }
