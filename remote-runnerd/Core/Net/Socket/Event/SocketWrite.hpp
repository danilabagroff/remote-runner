/**
 @file SocketRead.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Socekt_Event_SocketWrite_hpp
#define DrWeb_RemoteRunner_Core_Net_Socekt_Event_SocketWrite_hpp

#include "../SocketEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class SocketWrite final : public SocketEvent
	{
	/** @name Constructors */
	/** @{ */
	public:
		SocketWrite(const std::size_t bytes);
		SocketWrite(const SocketWrite& orig) = default;
		virtual ~SocketWrite() = default;
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
