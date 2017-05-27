/**
 @file SocketDown.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_Event_SocketDown_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_Event_SocketDown_hpp

#include "../SocketEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class SocketDown final : public SocketEvent
	{
	/** @name Constructors */
	/** @{ */
	public:
		SocketDown() = default;
		SocketDown(const SocketDown& orig) = default;
		virtual ~SocketDown() = default;
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
		virtual const std::string getAlias() const override;
	/** @} */
	};
} } } }

#endif
