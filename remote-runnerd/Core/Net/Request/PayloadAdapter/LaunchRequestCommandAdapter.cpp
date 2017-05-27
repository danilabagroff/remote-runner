/**
 @file LaunchRequestCommandAdapter.cpp
 @date 18.03.15

 @author Daniil A Megrabyan
*/

#include "LaunchRequestCommandAdapter.hpp"

#include "../../Buffer/CensoredBuffer.hpp"

#include "../../../../Wand/String.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	LaunchRequestCommandAdapter::LaunchRequestCommandAdapter(std::string& command)
	:
		_command(command)
	{

	}
	
	bool LaunchRequestCommandAdapter::init()
	{
		if (nullptr != _buffer) {
			return false;
		}
		
		_buffer = std::make_shared<CensoredBuffer>("\n");
		
		return AbstractPayloadAdapter::init();
	}
	
	void LaunchRequestCommandAdapter::digest()
	{
		std::getline(_stream, _command);
		wand::rtrim(_command);
	}
} } } }
