/**
 @file SocketEvent.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_SocketEvent_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_SocketEvent_hpp

#include "../AbstractEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class SocketEvent : public AbstractEvent
	{
	/** @name Constructors */
	/** @{ */
	public:
		SocketEvent() = default;
		SocketEvent(const SocketEvent& orig) = default;
		virtual ~SocketEvent() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
