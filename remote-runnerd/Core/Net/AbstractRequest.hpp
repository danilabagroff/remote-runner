/**
 @file AbstractRequest.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractRequest_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractRequest_hpp

#include "AbstractPayload.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractRequest : public AbstractPayload
	{
	/** @name Constructors */
	/** @{ */
	public:
		using AbstractPayload::AbstractPayload;
		virtual ~AbstractRequest() = default;
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual std::istream& getPayload() final;
		virtual const std::size_t getLength();
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
