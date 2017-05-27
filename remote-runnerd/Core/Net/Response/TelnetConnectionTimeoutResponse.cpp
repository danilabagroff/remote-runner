/**
 @file TelnetConnectionTimeoutResponse.cpp
 @date 03.03.15

 @author Daniil A Megrabyan
*/

#include "TelnetConnectionTimeoutResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	TelnetConnectionTimeoutResponse::TelnetConnectionTimeoutResponse()
	:
		TelnetLaunchResponse("Connection timeout, bye")
	{
	}
} } } }
