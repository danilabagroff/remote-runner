/**
 @file SocketRead.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Socket_Event_SocketRead_hpp
#define DrWeb_RemoteRunner_Core_Net_Socket_Event_SocketRead_hpp

#include "../SocketEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class SocketRead final : public SocketEvent
	{
	/** @name Constructors */
	/** @{ */
	public:
		SocketRead(const std::size_t bytes);
		SocketRead(const SocketRead& orig) = default;
		virtual ~SocketRead() = default;
	/** @} */
	
	/** @name Properties */
	/** @{ */
	private:
		const std::size_t _bytes;
	/** @} */
	
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::string getAlias() const override;
		const std::size_t getBytes() const;
	/** @} */
	};
} } } }

#endif
