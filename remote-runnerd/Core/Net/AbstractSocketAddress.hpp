/**
 @file AbstractSocketAddress.hpp
 @date 08.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractSocketAddress_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractSocketAddress_hpp

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {

	enum class SocketFamily : int
	{
		Unknown = AF_UNSPEC,
		Inet = 	AF_INET,
		Inet6 =	AF_INET6,
		Local = AF_LOCAL
	};
	
	class AbstractSocketAddress
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractSocketAddress() = default;
		AbstractSocketAddress(const AbstractSocketAddress&) = delete;
		AbstractSocketAddress& operator=(const AbstractSocketAddress&) = delete;
		virtual ~AbstractSocketAddress() = default;
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
		
	protected:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual void clear();
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
		virtual struct sockaddr* getPointer() = 0;
		virtual const SocketFamily getFamily() = 0;
		virtual const socklen_t getSize() = 0;
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
