/**
 @file LaunchRequestCommandAdapter.hpp
 @date 26.05.17

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Request_PayloadAdapter_LaunchRequestCommandAdapter_hpp
#define DrWeb_RemoteRunner_Core_Net_Request_PayloadAdapter_LaunchRequestCommandAdapter_hpp

#include "../../AbstractPayloadAdapter.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class LaunchRequestCommandAdapter : public AbstractPayloadAdapter
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		LaunchRequestCommandAdapter(std::string& command);
		virtual ~LaunchRequestCommandAdapter() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::string& _command;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool init() override;
		
	protected:
		virtual void digest() override;
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
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
