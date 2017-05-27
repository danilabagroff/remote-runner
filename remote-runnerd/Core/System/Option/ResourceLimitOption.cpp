/**
 @file ResourceLimitOption.cpp
 @date 26.06.15

 @author Daniil A Megrabyan
*/

#include "ResourceLimitOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	ResourceLimitOption::ResourceLimitOption(const ResourceLimitOption::Type type)
	:
		_type(type)
	{
		getrlimit(static_cast<int>(_type), &_limit);
	}
	
	bool ResourceLimitOption::operator()(std::istream& stream)
	{
		std::string limit;
		/// @xxx Поймать исключение и вернуть false
		stream >> limit;

		// зададим soft-limit
		_limit.rlim_cur = std::stoul(limit);
		// зададим hard-limit(потолок для soft-limit)
		_limit.rlim_max = std::stoul(limit);

		return true;
	}
	
	const struct rlimit& ResourceLimitOption::getLimit() const
	{
		return _limit;
	}
	
	const ResourceLimitOption::Type& ResourceLimitOption::getResourceType() const
	{
		return _type;
	}
} } } }
