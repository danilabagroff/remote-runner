/**
 @file LaunchRequest.hpp
 @date 2017-05-26
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Request_LaunchRequestCommand_hpp
#define DrWeb_RemoteRunner_Core_Net_Request_LaunchRequestCommand_hpp

#include "../AbstractRequest.hpp"

#include <string>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class LaunchRequest : public AbstractRequest
	{
	/** @name Constructors */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		LaunchRequest();
		virtual ~LaunchRequest() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::string _command;
	/** @} */

	/** @name Procedures */
	/** @{ */
	public:
		virtual void feed(std::ostream& stream) override;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const std::string& getCommand() const;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	protected:
	/** @} */
	};	
} } } }

#endif
