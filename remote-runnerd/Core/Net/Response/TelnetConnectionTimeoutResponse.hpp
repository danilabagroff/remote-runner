/**
 @file TelnetConnectionTimeoutResponse.hpp
 @date 03.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Response_TelnetConnectionTimeoutResponse_hpp
#define DrWeb_RemoteRunner_Core_Net_Response_TelnetConnectionTimeoutResponse_hpp

#include "TelnetLaunchResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class TelnetConnectionTimeoutResponse : public TelnetLaunchResponse
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		TelnetConnectionTimeoutResponse();
		virtual ~TelnetConnectionTimeoutResponse() = default;
	/** @} */
	};
} } } }

#endif
