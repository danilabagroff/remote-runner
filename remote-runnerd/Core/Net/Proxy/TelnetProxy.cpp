/**
 @file TelnetProxy.cpp
 @date 14.09.15

 @author Daniil A Megrabyan
*/

#include "TelnetProxy.hpp"

#include "../Log.hpp"
#include "../Response/TelnetConnectionTimeoutResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	TelnetProxy::TelnetProxy(std::shared_ptr<Connection> connection, Core::Launcher& launcher)
	:
		AbstractProxy(connection),
		_launcher(launcher),
		_request(new LaunchRequest())
	{
		
	}
	
	std::shared_ptr<AbstractProxy> TelnetProxy::transmit()
	{
		AbstractProxy::transmit();
		
		/// Защита от дурака
		if (nullptr == _request) {
			return nullptr;
		}
		
		/// Пополняем буфер пока есть чем
		while (_connection->getBuffer().getSize() > 0) {
			_connection->pull(_request);
			
			/// Если буфер закончен(загружен), то создаем новый буфер, а старый обрабатываем
			if (_request->isLoaded()) {
				std::shared_ptr<LaunchRequest> request(_request);
				_request.reset(new LaunchRequest());
				
				if (!_launcher.exec(request->getCommand(), _connection)) {
					LogRegister<Net::Log>::Debug("TelnetProxy(", this, ") > Launch has failed");
				}
			} else {
				break;
			}
		}
		
		return shared_from_this();
	}
	
	void TelnetProxy::dispose()
	{
		AbstractProxy::dispose();
	}
	
	const std::string TelnetProxy::getAlias()
	{
		return "TelnetProxy";
	}
	
	const bool TelnetProxy::isValid()
	{
		/// @todo Брать из конфига
		std::chrono::seconds timeout(100);

		std::chrono::system_clock::time_point now(std::chrono::system_clock::now());
		if (now - _connection->getLastActivityTimePoint() >= timeout) {
			LogRegister<Net::Log>::Debug("TelnetProxy(", this, ") * Connection timeout");
			_connection->push(std::make_shared<Core::Net::TelnetConnectionTimeoutResponse>());
			
			return false;
		}
		
		return true;
	}
} } } }
