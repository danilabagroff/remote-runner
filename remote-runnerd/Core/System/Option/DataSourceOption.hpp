/**
 @file DataSourceOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_DataSourceOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_DataSourceOption_hpp

#include "URIOption.hpp"

#include <string>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class DataSourceOption : public URIOption
	{
	/** @name Classes */
	/** @{ */
	public:
		enum class Family
		{
			Unknown,
			ODBC,
			PotgreSQL,
			MySQL,
			Firebird,
			Excel,
			CSV
		};
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		DataSourceOption(const std::string& connection_string);
		DataSourceOption(const DataSourceOption::Family& source_family, const std::string& connection_string, const std::string& username, const std::string& password);
		DataSourceOption(const wand::uri& uri);
		virtual ~DataSourceOption() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	private:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
	/** @} */

	/** @name Properties */
	/** @{ */
	private:
		DataSourceOption::Family _family;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	private:
		bool parse();
	/** @} */
	
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const DataSourceOption::Family getFamily() const;
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
