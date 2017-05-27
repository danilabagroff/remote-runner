/**
 @file AbstractServer.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractServer_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractServer_hpp

#include "Connection.hpp"
#include "AbstractProxy.hpp"
#include "Socket/ServerSocket.hpp"

#include <utility>
#include <map>
#include <queue>
#include <future>
#include <memory>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractServer
	{
	/** @name Classes */
	/** @{ */
	public:
		enum class Signal
		{
			Unknown,
			Interruption,
			Termination,
			Quit,
			HangUp
		};
	/** @} */

	/** @name Aliases */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		explicit AbstractServer(std::unique_ptr<ServerSocket> socket);
		AbstractServer(const AbstractServer&) = delete;
		AbstractServer& operator=(const AbstractServer&) = delete;
		virtual ~AbstractServer() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
		bool _online;
		const std::unique_ptr<ServerSocket> _socket;
	/** @} */

	/** @name Procedures */
	/** @{ */
	protected:
		virtual const std::shared_ptr<AbstractProxy> makeProxy(std::shared_ptr<Connection> connection) const = 0;
	/** @} */

	/** @name Procedures */
	/** @{ */
	public:
		virtual bool run();
	/** @} */

	/** @name Hooks */
	/** @{ */
	protected:
		virtual bool onSignal(AbstractServer::Signal sig);
	/** @} */
	};
} } } }
#endif
