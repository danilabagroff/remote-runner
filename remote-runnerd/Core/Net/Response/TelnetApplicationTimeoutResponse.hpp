/**
 @file TelnetConnectionTimeoutResponse.hpp
 @date 03.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Response_TelnetApplicationTimeoutResponse_hpp
#define DrWeb_RemoteRunner_Core_Net_Response_TelnetApplicationTimeoutResponse_hpp

#include "TelnetLaunchResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class TelnetApplicationTimeoutResponse : public TelnetLaunchResponse
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		TelnetApplicationTimeoutResponse();
		virtual ~TelnetApplicationTimeoutResponse() = default;
	/** @} */
	};
} } } }

#endif
