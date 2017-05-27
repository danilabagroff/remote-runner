/**
 @file LinuxServer.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Server_LinuxServer_hpp
#define DrWeb_RemoteRunner_Core_Net_Server_LinuxServer_hpp

#include "../AbstractServer.hpp"

#include "../Transmission.hpp"

#include <sys/signalfd.h>
#include <map>
#include <utility>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class Server : public AbstractServer
	{
	/** @name Aliases */
	/** @{ */
	public:
		using PollMap = std::map<int, std::pair<int, std::shared_ptr<Transmission>>>;
	/** @} */

	/** @name Constructors */
	/** @{ */
	public:
		Server(std::unique_ptr<ServerSocket> socket);
		virtual ~Server() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		sigset_t _signal_set;
		Server::PollMap _socket_map;
		Server::PollMap _timer_map;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual bool run() override;
	/** @} */

	/** @name Setters */
	/** @{ */
	private:
		bool setTimer(const int handle, const int timeout = 50);
	/** @} */

		/** @name Hooks */
	/** @{ */
	protected:
		using AbstractServer::onSignal;
		bool onSignal(uint32_t sig);
	/** @} */
	};
} } } }
#endif
