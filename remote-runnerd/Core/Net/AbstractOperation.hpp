/**
 @file
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractOperation_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractOperation_hpp

#include "AbstractResponse.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractAgent;
	
	class AbstractOperation
	{
	/** @name Procedures  */
	/** @{ */
	public:
		virtual void invoke() = 0;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::string getAlias() const = 0;
		virtual std::shared_ptr<AbstractResponse> getResponse() const = 0;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
		virtual void resetAgent(std::shared_ptr<AbstractAgent> agent) const = 0;
	/** @} */
	};
} } } }

#endif
