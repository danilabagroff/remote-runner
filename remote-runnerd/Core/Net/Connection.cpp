/**
 @file Connection.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "Connection.hpp"

#include "Log.hpp"
#include <ostream>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	Connection::Connection(std::unique_ptr<ClientSocket> socket)
	:
		_socket(std::move(socket)),
		_last_pull(std::chrono::system_clock::now()),
		_last_push(std::chrono::system_clock::now())
	{
		LogRegister<Net::Log>::Debug("Connection(", this, ", ", _socket->getHandle(), ") > Instance has been created");
	}
	
	Connection::Connection(Connection&& origin)
	:
		_socket(std::move(origin._socket))
	{
		origin._socket = nullptr;
	}
	
	Connection::~Connection()
	{
		LogRegister<Net::Log>::Debug("Connection(", this, ", ", _socket->getHandle(), ") * Instance is going to be destroyed...");
		_socket = nullptr;
		/// @todo _buffer.clear();
	}
	
	std::size_t Connection::pull(std::shared_ptr<AbstractPayload> payload)
	{
		if (nullptr == _socket) {
			return 0;
		}
		
		if (nullptr != payload) {
			LogRegister<Net::Log>::Error("Connection(", this, ") * Pre-Extracting bytes from buffer(", _buffer.getSize(), ") to the payload adapter...");
			if (payload->consume(_buffer)) {
				return _buffer.getSize();
			}
		}
		
		LogRegister<Net::Log>::Debug("Connection(", this, ") * Pulling all currently avaliable data...");
		_last_pull = std::chrono::system_clock::now();
		std::size_t count(_socket->read(_buffer));
		
		if (0 == count && _socket->isFailed()) {
			LogRegister<Net::Log>::Error("Connection(", this, ") > Couldn't read any data from socket: ", getSocketError());
			return 0;
		} else {
			LogRegister<Net::Log>::Error("Connection(", this, ") > Read ", count, " bytes; Total ", _buffer.getSize(), " bytes");
		}
		
		if (nullptr != payload) {
			LogRegister<Net::Log>::Error("Connection(", this, ") * Post-Extracting bytes from buffer(", _buffer.getSize(), ") to the payload adapter...");
			payload->consume(_buffer);
		}
		
		return _buffer.getSize();
	}
	
	std::size_t Connection::push(std::shared_ptr<AbstractPayload> payload)
	{
		if (nullptr == payload || nullptr == _socket) {
			return false;
		}
		
		FlexibleBuffer buffer;
		std::ostream stream(&buffer);
		payload->feed(stream);
		
		LogRegister<Net::Log>::Debug("Connection(", this, ") * Sending ", buffer.getSize(), " bytes(s)...");
		_last_push = std::chrono::system_clock::now();
		
		return _socket->write(buffer);
	}

	const int Connection::getDescriptor() const
	{
		return nullptr == _socket ? 0 : _socket->getHandle();
	}
	
	const std::string Connection::getSocketError() const
	{
		return nullptr == _socket ? "" : _socket->getError();
	}
	
	const std::chrono::system_clock::time_point& Connection::getLastPullTimePoint() const
	{
		return _last_pull;
	}
	
	const std::chrono::system_clock::time_point& Connection::getLastPushTimePoint() const
	{
		return _last_push;
	}
	
	const std::chrono::system_clock::time_point& Connection::getLastActivityTimePoint() const
	{
		return _last_push > _last_pull ? _last_push : _last_pull;
	}
	
	const FlexibleBuffer& Connection::getBuffer() const
	{
		return _buffer;
	}
	
	const bool Connection::hasSocket() const
	{
		return (nullptr != _socket);
	}
} } } }
