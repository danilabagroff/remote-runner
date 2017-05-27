/**
 @file BSDServer.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Server_BSDServer_hpp
#define DrWeb_RemoteRunner_Core_Net_Server_BSDServer_hpp

#include "../AbstractServer.hpp"

#include "../Transmission.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class Server : public AbstractServer
	{
	/** @name Aliases */
	/** @{ */
	public:
		using PollMap = std::map<int, const std::shared_ptr<Transmission>>;
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
		PollMap _poll;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual bool run() override;

	private:
		virtual Server::PollMap::iterator accept(int& socket) final;
		virtual bool reject(Server::PollMap::iterator iterator) final;
		virtual bool receive(Server::PollMap::iterator iterator) final;
		virtual bool assert(Server::PollMap::iterator iterator) final;
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	protected:
		using AbstractServer::onSignal;
		bool onSignal(unsigned short int sig);
	/** @} */
	};
} } } }

#endif
