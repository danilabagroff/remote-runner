/**
 @file AbstractServer.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractServer.hpp"

#include "../../Wand/AsyncThen.hpp"
#include "Log.hpp"

#include <list>
#include <memory>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	AbstractServer::AbstractServer(std::unique_ptr<ServerSocket> socket)
	:
		_online(false),
		_socket(std::move(socket))
	{

	}

	bool AbstractServer::run()
	{
		LogRegister<Net::Log>::Notice("AbstractServer(", this, ") * Starting socket server...");

		if (!_socket->init()) {
			LogRegister<Net::Log>::Fatal("AbstractServer(", this, ") > Socket has not been initialized: ", _socket->getError());
			return false;
		}

		return (_online = true);
	}
	
	bool AbstractServer::onSignal(AbstractServer::Signal sig)
	{
		switch (sig) {
			case AbstractServer::Signal::Quit:
			case AbstractServer::Signal::Interruption:
				LogRegister<Net::Log>::Warning("Server > Interuption(or quit) signal was caught");
				return true;
				break;
			case AbstractServer::Signal::Termination:
				LogRegister<Net::Log>::Warning("Server > Termination signal was caught");
				return true;
				break;
			case AbstractServer::Signal::HangUp:
				LogRegister<Net::Log>::Warning("Server > Reload was requested");
				return false;
				break;
			default:
				LogRegister<Net::Log>::Warning("Server > Unexpected signal was caught");
			break;
		}

		return false;
	}
} } } }
