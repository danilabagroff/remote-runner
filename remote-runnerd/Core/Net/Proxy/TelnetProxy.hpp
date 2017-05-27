/**
 @file TelnetProxy.hpp
 @date 14.09.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Proxy_TelnetProxy_hpp
#define DrWeb_RemoteRunner_Core_Net_Proxy_TelnetProxy_hpp

#include "../AbstractProxy.hpp"

#include "../../Launcher.hpp"
#include "../Request/LaunchRequest.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class TelnetProxy : public AbstractProxy
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		TelnetProxy(std::shared_ptr<Connection> connection, Core::Launcher& launcher);
		virtual ~TelnetProxy() = default;
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		Core::Launcher& _launcher;
		std::shared_ptr<LaunchRequest> _request;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual std::shared_ptr<AbstractProxy> transmit() override;
		virtual void dispose() override;
	/** @} */
		
	/** @name Converters */
	/** @{ */
	public:
	/** @} */
	
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::string getAlias() override;
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		virtual const bool isValid() override;
	/** @} */
	};
} } } }

#endif
