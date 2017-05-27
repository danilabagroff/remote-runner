/**
 @file TelnetLaunchResponse.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Response_TelnetLaunchResponse_hpp
#define DrWeb_RemoteRunner_Core_Net_Response_TelnetLaunchResponse_hpp

#include "../AbstractResponse.hpp"

#include <string>
#include <map>
#include <iostream>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class TelnetLaunchResponse : public AbstractResponse
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		TelnetLaunchResponse(std::string output);
		TelnetLaunchResponse();
		virtual ~TelnetLaunchResponse();
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
		std::string _output;
	/** @} */
	
	/** @name Operators */
	/** @{ */
	public:
		virtual void feed(std::ostream& stream) override;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	private:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
	/** @} */

	/** @name States */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
