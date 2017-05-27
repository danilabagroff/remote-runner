/**
 @file AbstractEvent.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractEvent.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	bool AbstractEvent::operator==(const std::uint16_t& rhs) const
	{
		return (getType() == rhs && getType() != 0x0);
	}
} } }
