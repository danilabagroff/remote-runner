/**
 @file ServerSocket.hpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_ServerSocket_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_ServerSocket_hpp

#include "../AbstractSocket.hpp"
#include "ClientSocket.hpp"

#include <string>
#include <netdb.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class ServerSocket : public AbstractSocket
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		ServerSocket(std::unique_ptr<AbstractSocketAddress> address);
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
		std::unique_ptr<ClientSocket> accept() const;
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool init() override;
	/** @} */
		
	/** @name Converters */
	/** @{ */
	public:
	/** @} */
	
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
