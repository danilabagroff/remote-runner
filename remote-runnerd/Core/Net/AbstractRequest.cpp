/**
 @file AbstractRequest.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractRequest.hpp"

#include <strstream>
#include <iostream>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	std::istream& AbstractRequest::getPayload()
	{
		return _payload;
	}

	const std::size_t AbstractRequest::getLength()
	{
		std::streampos zero_offset = _payload.tellg();
		if (zero_offset < 0) {
			return 0;
		}
		_payload.seekg(0, std::ios::end);
		std::streampos end_offset = _payload.tellg();
		_payload.seekg(zero_offset);
		
		return static_cast<std::size_t>(end_offset);
		
		return 0;		
	}
} } } }
