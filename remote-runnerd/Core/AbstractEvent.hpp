/**
 @file AbstractEvent.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_AbstractEvent_hpp
#define DrWeb_RemoteRunner_Core_AbstractEvent_hpp

#include "AbstractInputStream.hpp"

#include "../Wand/Type.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class AbstractEvent
	{
	/** @name Constructors */
	public:
		virtual ~AbstractEvent() = default;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual void apply(AbstractInputStream& stream) = 0;
	/** @} */

	/** @name Operators */
	/** @{ */
	public:
		bool operator==(const std::uint16_t& rhs) const;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const std::string getAlias() const = 0;
		virtual const std::uint16_t getType() const = 0;
	/** @} */
	};
} } }

#endif
