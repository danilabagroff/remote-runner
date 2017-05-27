/**
 @file SwitchOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "SwitchOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	SwitchOption::SwitchOption(const bool onoff)
	:
		_onoff(onoff)
	{
		
	}
	
	bool SwitchOption::operator()(std::istream& stream)
	{
		std::string level;
		stream >> level;
		
		if (level.compare("on") == 0) {
			_onoff = true;
		} else if (level.compare("off") == 0) {
			_onoff = false;
		} else {
			return false;
		}
		
		return true;
	}
	
	const bool& SwitchOption::getState() const
	{
		return _onoff;
	}
	
	bool SwitchOption::isOn() const
	{
		return _onoff;
	}
} } } }
