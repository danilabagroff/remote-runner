/**
 @file AbstractPreference.cpp
 @date 11.06.15

 @author Daniil A Megrabyan
*/

#include "AbstractPreference.hpp"

#include <cstdlib>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	AbstractPreference::AbstractPreference(const std::string section_name, std::initializer_list<std::pair<const std::string, AbstractOption&>> map)
	:
		_section_name(section_name),
		_map(map)
	{

	}
	
	const std::string& AbstractPreference::getSectionName() const
	{
		return _section_name;
	}
	
	AbstractPreference::OptionMap::const_iterator AbstractPreference::cbegin()
	{
		return _map.cbegin();
	}
	
	AbstractPreference::OptionMap::const_iterator AbstractPreference::cend()
	{
		return _map.cend();
	}
	
	AbstractPreference::OptionMap::const_iterator AbstractPreference::find(AbstractPreference::OptionMap::key_type key)
	{
		return _map.find(key);
	}
} } } }
