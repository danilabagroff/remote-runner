/**
 @file LicenseOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "LicenseOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	LicenseOption::LicenseOption(LicenseOption::Type type)
	:
		_type(type)
	{
		
	}
	
	bool LicenseOption::operator()(std::istream& stream)
	{
		std::string type;
		stream >> type;
		
		if (type.compare("debug") == 0) {
			_type = LicenseOption::Type::Debug;
		} else if (type.compare("demo") == 0) {
			_type = LicenseOption::Type::Demo;
		} else if (type.compare("test") == 0) {
			_type = LicenseOption::Type::Test;
		} else if (type.compare("server") == 0) {
			_type = LicenseOption::Type::Server;
		} else if (type.compare("key") == 0) {
			_type = LicenseOption::Type::Key;
		} else if (type.compare("dongle") == 0) {
			_type = LicenseOption::Type::Dongle;
		} else {
			_type = LicenseOption::Type::Unknown;
			return false;
		}		

		return true;
	}
	
	const LicenseOption::Type& LicenseOption::getType() const
	{
		return _type;
	}
} } } }
