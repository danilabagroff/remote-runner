/**
 @file SocketError.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_Event_SocketError_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_Event_SocketError_hpp

#include "../SocketEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class SocketError final : public SocketEvent
	{
	/** @name Constructors */
	/** @{ */
	public:
		SocketError(const std::string message);
		SocketError(const SocketError& orig) = default;
		virtual ~SocketError() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		const std::string _message;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::string getAlias() const override;
		const std::string& getMessage() const;
	/** @} */
	};
} } } }

#endif
