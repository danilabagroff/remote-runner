/**
 @file AbstractEvent.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractEvent_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractEvent_hpp

#include "../AbstractEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractEvent : public Core::AbstractEvent
	{
	/** @name Constructors */
	/** @{ */
	public:
		virtual ~AbstractEvent() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual void apply(AbstractInputStream& stream) final override;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::uint16_t getType() const final override;
	/** @} */
	};
} } } }

#endif
