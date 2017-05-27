/**
 @file TelnetServer.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "TelnetServer.hpp"

#include "../Proxy/TelnetProxy.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	TelnetServer::TelnetServer(std::unique_ptr<ServerSocket> socket, Core::Launcher& launcher)
	:
		_launcher(launcher),
		Server(std::move(socket))
	{
		
	}
	
	const std::shared_ptr<AbstractProxy> TelnetServer::makeProxy(std::shared_ptr<Connection> connection) const
	{
		return std::make_shared<TelnetProxy>(connection, _launcher);
	}
	
	bool TelnetServer::onSignal(AbstractServer::Signal sig)
	{
		if (Server::onSignal(sig)) {
			return true;
		}
		
		switch (sig) {
			case AbstractServer::Signal::Quit:
			case AbstractServer::Signal::Interruption:
				return true;
				break;
			case AbstractServer::Signal::Termination:
				return true;
				break;
			case AbstractServer::Signal::HangUp:
				_launcher.reload();
				return false;
				break;
			default:
				break;
		}
		
		return false;
	}
} } } }
