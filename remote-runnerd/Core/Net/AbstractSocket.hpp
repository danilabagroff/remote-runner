/**
 @file AbstractSocket.hpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractSocket_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractSocket_hpp

#include "AbstractSocketAddress.hpp"
#include "Buffer/FlexibleBuffer.hpp"

#include "Socket/Event/SocketUp.hpp"
#include "Socket/Event/SocketDown.hpp"
#include "Socket/Event/SocketRead.hpp"
#include "Socket/Event/SocketWrite.hpp"
#include "Socket/Event/SocketError.hpp"

#include "../../Wand/Listener.hpp"
#include <memory>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractSocket : public wand::listener<SocketDown, SocketUp/*, SocketRead, SocketWrite, SocketError*/>
	{
	/** @name Constants */
	/** @{ */
	public:
		static const std::size_t Batch;
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractSocket(std::unique_ptr<AbstractSocketAddress> address);
		AbstractSocket(const AbstractSocket&) = delete;
		AbstractSocket& operator=(const AbstractSocket&) = delete;
		virtual ~AbstractSocket();
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
		std::unique_ptr<AbstractSocketAddress> _address;
		int _handle;
		int _last_error;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool init();
		virtual const std::size_t write(const FlexibleBuffer& buffer) final;
		virtual const std::size_t read(FlexibleBuffer& buffer, bool dont_wait = true) final;
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
		virtual const int getHandle() const final;
		const char* getError() const;
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		const bool isFailed() const;
		const bool isValid() const;
	/** @} */
	};
} } } }

#endif
