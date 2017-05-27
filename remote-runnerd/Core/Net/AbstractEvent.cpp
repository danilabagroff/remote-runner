/**
 @file AbstractEvent.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#include "AbstractEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	void AbstractEvent::apply(AbstractInputStream& stream)
	{
		
	}
	
	const std::uint16_t AbstractEvent::getType() const
	{
		return 0x0000;
	}
} } } }
