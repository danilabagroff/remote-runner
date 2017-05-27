/**
 @file Map.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef Wand_Map_hpp
#define Wand_Map_hpp

#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

namespace wand {
	template<class T>
	struct map_value_find : public std::binary_function<typename T::value_type, typename T::mapped_type, bool>
	{
	public:
		bool operator() (const typename T::value_type &pair, typename T::mapped_type i) const
		{
			return pair.second == i;
		}
	};

}
#endif
