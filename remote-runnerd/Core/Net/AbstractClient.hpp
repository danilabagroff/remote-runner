/**
 @file AbstractClient.hpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractClient_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractClient_hpp

#include "Socket/ClientSocket.hpp"
#include "AbstractRequest.hpp"
#include "AbstractResponse.hpp"
#include <memory>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractClient
	{
	/** @name Constants */
	/** @{ */
	public:
		static const std::size_t Batch;
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractClient(std::unique_ptr<ClientSocket> socket);
		AbstractClient(const AbstractClient&) = delete;
		AbstractClient& operator=(const AbstractClient&) = delete;
		virtual ~AbstractClient();
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
		const std::unique_ptr<ClientSocket> _socket;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool send(AbstractRequest& request, AbstractResponse& response) = 0;
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
	protected:
		const int getSocketHandle();
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
