/**
 @file UnixSocketAddress.hpp
 @date 08.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_UnixSocketAddress_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_UnixSocketAddress_hpp

#include "../AbstractSocketAddress.hpp"

#include <string>
#include <sys/un.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class UnixSocketAddress : public AbstractSocketAddress
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		UnixSocketAddress(const std::string path);
		virtual ~UnixSocketAddress() = default;
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
		struct sockaddr_un _address;
		
	protected:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual void clear() override;
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
