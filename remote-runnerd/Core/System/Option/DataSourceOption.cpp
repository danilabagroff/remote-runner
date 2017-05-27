/**
 @file DataSourceOption.cpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#include "DataSourceOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	DataSourceOption::DataSourceOption(const std::string& connection_string)
	:
		URIOption(connection_string),
		_family(DataSourceOption::Family::Unknown)
	{
		parse();
	}

	DataSourceOption::DataSourceOption(const DataSourceOption::Family& source_family, const std::string& connection_string, const std::string& username, const std::string& password)
	:
		URIOption(/*family + */"://" +  username + ":" + password + "@" + connection_string),
		_family(source_family)
	{
		parse();
	}
	
	DataSourceOption::DataSourceOption(const wand::uri& uri)
	:
		URIOption(uri),
		_family(DataSourceOption::Family::Unknown)
	{
		parse();
	}
	
	bool DataSourceOption::operator()(std::istream& stream)
	{
		if (!URIOption::operator()(stream)) {
			return false;
		}
		
		return parse();
	}
	
	bool DataSourceOption::parse()
	{
		if (getScheme().compare("odbc") == 0) {
			_family = DataSourceOption::Family::ODBC;
		} else if (getScheme().compare("postgresql") == 0) {
			_family = DataSourceOption::Family::PotgreSQL;
		} else if (getScheme().compare("mysql") == 0) {
			_family = DataSourceOption::Family::MySQL;
		} else if (getScheme().compare("firebird") == 0) {
			_family = DataSourceOption::Family::Firebird;
		} else if (getScheme().compare("excel") == 0) {
			_family = DataSourceOption::Family::Excel;
		} else if (getScheme().compare("csv") == 0) {
			_family = DataSourceOption::Family::CSV;
		} else {
			_family = DataSourceOption::Family::Unknown;
			return false;
		}
		
		return true;
	}

	const DataSourceOption::Family DataSourceOption::getFamily() const
	{
		return _family;
	}
} } } }
