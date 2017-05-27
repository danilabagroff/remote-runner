/**
 @file TelnetServer.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Server_TelnetServer_hpp
#define DrWeb_RemoteRunner_Core_Net_Server_TelnetServer_hpp

#include "Server.hpp"

#include "../../Launcher.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class TelnetServer final : public Server
	{
	/** @name Constructors */
	/** @{ */
	public:
		TelnetServer(std::unique_ptr<ServerSocket> socket, Core::Launcher& launcher);
		virtual ~TelnetServer() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		Core::Launcher& _launcher;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	protected:
		virtual const std::shared_ptr<AbstractProxy> makeProxy(std::shared_ptr<Connection> connection) const override;
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	protected:
		bool onSignal(AbstractServer::Signal sig) override;
	/** @} */
	};
} } } }
#endif
