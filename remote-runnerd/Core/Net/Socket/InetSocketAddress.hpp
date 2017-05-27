/**
 @file InetSocketAddress.hpp
 @date 08.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_InetSocketAddress_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_InetSocketAddress_hpp

#include "../AbstractSocketAddress.hpp"

#include <string>
#include <netinet/in.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class InetSocketAddress : public AbstractSocketAddress
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		InetSocketAddress(const std::string host, const unsigned short port);
		InetSocketAddress(const unsigned short port);
		InetSocketAddress();
		virtual ~InetSocketAddress() = default;
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
	private:
		struct sockaddr_in _address;
		
	protected:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
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
		virtual struct sockaddr* getPointer() override;
		virtual const SocketFamily getFamily() override;		
		virtual const socklen_t getSize() override;
		
		const std::string getHost();
		const unsigned short getPort();
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
