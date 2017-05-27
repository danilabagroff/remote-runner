/**
 @file Connection.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Connection_hpp
#define DrWeb_RemoteRunner_Core_Net_Connection_hpp

#include "AbstractPayload.hpp"
#include "Socket/ClientSocket.hpp"
#include "Buffer/FlexibleBuffer.hpp"

#include <memory>
#include <atomic>
#include <chrono>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class Connection final
	{
	/** @name Constructors */
	/** @{ */
	public:
		explicit Connection(std::unique_ptr<ClientSocket> socket);
		Connection(Connection&& origin);
		Connection(const Connection&) = delete;
		Connection& operator=(const Connection&) = delete;
		virtual ~Connection();
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::unique_ptr<AbstractSocket> _socket;
		FlexibleBuffer _buffer;
		
		std::chrono::system_clock::time_point _last_pull;
		std::chrono::system_clock::time_point _last_push;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		std::size_t pull(std::shared_ptr<AbstractPayload> payload = nullptr);
		std::size_t push(std::shared_ptr<AbstractPayload> payload);
	/** @} */
		
	/** @name Getters  */
	/** @{ */
	public:
		const int getDescriptor() const;
		const std::string getSocketError() const;
		
		const std::chrono::system_clock::time_point& getLastPullTimePoint() const;
		const std::chrono::system_clock::time_point& getLastPushTimePoint() const;
		const std::chrono::system_clock::time_point& getLastActivityTimePoint() const;
		
		const FlexibleBuffer& getBuffer() const;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
		template<typename TListener>
		void addEventListener(TListener&& listener)
		{
			_socket->add(std::forward<TListener>(listener));
		};
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		const bool hasSocket() const;		
	/** @} */
	};
} } } }

namespace std {
	template <> struct hash<DrWeb::RemoteRunner::Core::Net::Connection>
	{
		std::size_t operator()(const DrWeb::RemoteRunner::Core::Net::Connection& c) const
		{
			return std::hash<std::size_t>()(c.getDescriptor());
		}
	};
}

#endif
