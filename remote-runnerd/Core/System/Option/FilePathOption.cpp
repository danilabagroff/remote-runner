/**
 @file FilePathOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "FilePathOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	FilePathOption::FilePathOption(const std::string& path)
	:
		_path(path)
	{
		
	}
	
	bool FilePathOption::operator()(std::istream& stream)
	{
		stream >> _path;
		
		return true;
	}
	
	const std::string& FilePathOption::getPath() const
	{
		return _path;
	}
} } } }
