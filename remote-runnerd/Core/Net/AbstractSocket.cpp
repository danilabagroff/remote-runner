/**
 @file AbstractSocket.cpp
 @date 05.03.15

 @author Daniil A Megrabyan
*/

#include "AbstractSocket.hpp"

#include "Log.hpp"
#include <array>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	const std::size_t AbstractSocket::Batch = 4048;
	
	AbstractSocket::AbstractSocket(std::unique_ptr<AbstractSocketAddress> address)
	:
		_address(std::move(address)),
		_handle(0),
		_last_error(0)
	{

	}
	
	AbstractSocket::~AbstractSocket()
	{
		if (_handle > 0) {
			close(_handle);
			SocketDown event;
			on(event);
			
			LogRegister<Net::Log>::Notice("AbstractSocket(", _handle, ") > Disconnected");
		}
	}
	
	bool AbstractSocket::init()
	{
		if (_handle > 0) {
			return true;
		}
		
		_handle = socket(static_cast<int>(_address->getFamily()), SOCK_STREAM, 0);

		if (_handle <= 0) {
			_last_error = errno;
			SocketError event("Couldn't init socket: " + std::to_string(_last_error));
			//on(event);
			
			return false;
		}

		SocketUp event;
		//on(event);
		
		return true;
	}
	
	const std::size_t AbstractSocket::write(const FlexibleBuffer& buffer)
	{
		ssize_t count = send(_handle, buffer.getVector().data(), buffer.getSize(), MSG_DONTWAIT);
		SocketWrite event(count);
		//on(event);
		
		return count;
	}
	
	const std::size_t AbstractSocket::read(FlexibleBuffer& buffer, bool dont_wait)
	{
		std::array<char, AbstractSocket::Batch> batch;
		ssize_t count = 0;		
		do {
			// Читаем то, что дают — не ждем данных для всего батча
			count = recv(_handle, batch.begin(), batch.size(), MSG_DONTWAIT);

			if (count < 0 && buffer.getSize() == 0) {
				if (errno == EAGAIN) {
					//count = 1;
					//continue;
					break ;
				}
				
				_last_error = errno;

				LogRegister<Net::Log>::Error("AbstractSocket(", _handle, ") > Error(", _last_error, ") on receiving data: ", strerror(_last_error));
				SocketError event("Couldn't read from the socket: " + std::to_string(_last_error));
				//on(event);
				
				return 0;
			}
			
			if (count > 0) {
				buffer.sputn(batch.begin(), count);
				SocketRead event(count);
				//on(event);
			}
			
		} while (count > 0); // Читаем пока есть, что читать
		
		return buffer.getSize();
	}
	
	const int AbstractSocket::getHandle() const
	{
		return _handle;
	}
	
	const char* AbstractSocket::getError() const
	{
		return strerror(_last_error);
	}
	
	const bool AbstractSocket::isFailed() const
	{
		return (0 != _last_error);
	}
	
	const bool AbstractSocket::isValid() const
	{
		return (_handle > 0);
	}
} } } }
