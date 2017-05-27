/**
 @file AbstractProxy.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractProxy_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractProxy_hpp

#include "AbstractResponse.hpp"
#include "Connection.hpp"

#include <memory>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractProxy : public std::enable_shared_from_this<AbstractProxy>
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractProxy(std::shared_ptr<Connection> connection);
		virtual ~AbstractProxy() = default;
	/** @} */

	/** @name Members */
	/** @{ */
	protected:
		std::shared_ptr<Connection> _connection;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */

	/** @name Procedures */
	/** @{ */
	public:
		virtual std::shared_ptr<AbstractProxy> transmit();
		virtual void dispose();
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::string getAlias() = 0;
		const std::shared_ptr<const Connection> getConnection() const;
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		virtual const bool isValid() = 0;
	/** @} */
	};
} } } }

#endif
