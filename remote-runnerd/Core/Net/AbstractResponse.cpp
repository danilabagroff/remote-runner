/**
 @file
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractResponse.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	void AbstractResponse::append(const std::string& data)
	{
		_payload.write(data.c_str(), data.size());
	}
	
	void AbstractResponse::append(const std::uint16_t data)
	{
		std::string x((char*)&data, sizeof(data));
		append(x);
	}
	
	void AbstractResponse::append(const std::uint32_t data)
	{
		std::string x((char*)&data, sizeof(data));
		append(x);
	}
	
	std::ostream& AbstractResponse::getPayload()
	{
		return _payload;
	}
	
	std::size_t AbstractResponse::getStreamLength()
	{
		std::stringstream::pos_type zero_offset = _payload.tellp();
		if (zero_offset < 0) {
			return 0;
		}
		_payload.seekp(0, std::ios::end);
		std::stringstream::pos_type end_offset = _payload.tellp();
		_payload.seekp(zero_offset);

		return static_cast<std::size_t>(end_offset);
	}
	
	std::size_t AbstractResponse::getStreamPosition()
	{
		std::stringstream::pos_type zero_offset = _payload.tellp();
		
		return static_cast<std::size_t>(zero_offset);
	}
} } } }
