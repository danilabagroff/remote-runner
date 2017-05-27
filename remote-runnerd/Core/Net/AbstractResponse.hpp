/**
 @file AbstractRequest.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractResponse_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractResponse_hpp

#include "AbstractPayload.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {	
	class AbstractResponse : public AbstractPayload
	{
	/** @name Constructors */
	/** @{ */
	public:
		using AbstractPayload::AbstractPayload;
		virtual ~AbstractResponse() =default;
	/** @} */

	/** @name Properties */
	/** @{ */
	protected:
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual void append(const std::string& data) final;
		virtual void append(const std::uint16_t data) final;
		virtual void append(const std::uint32_t data) final;
	/** @} */
			
	/** @name Getters */
	/** @{ */
	public:
		virtual std::ostream& getPayload();
		
	protected:
		virtual std::size_t getStreamLength() final;
		virtual std::size_t getStreamPosition() final;
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
