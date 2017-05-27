/**
 @file AbstractProxy.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractProxy.hpp"
#include "Log.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	AbstractProxy::AbstractProxy(std::shared_ptr<Connection> connection)
	:
		_connection(connection)
	{
		
	}
	
	std::shared_ptr<AbstractProxy> AbstractProxy::transmit()
	{
		LogRegister<Net::Log>::Debug("AbstractProxy(", this, ") * Transmit...");
		_connection->pull();
		
		return shared_from_this();
	}
	
	void AbstractProxy::dispose()
	{
		_connection.reset();
	}
	
	const std::shared_ptr<const Connection> AbstractProxy::getConnection() const
	{
		return _connection;
	}
} } } }
