/**
 @file StreamException.cpp
 @date 02.04.16

 @author Daniil A Megrabyan
*/

#include "StreamException.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	const StreamException::Code& StreamException::getCode() const
	{
		return _code;
	}
} } }
