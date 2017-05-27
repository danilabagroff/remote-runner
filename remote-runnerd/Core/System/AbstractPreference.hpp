/**
 @file AbstractPreference.hpp
 @date 11.06.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_System_AbstractPreference_hpp
#define DrWeb_RemoteRunner_Core_System_AbstractPreference_hpp

#include "AbstractOption.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class AbstractPreference
	{
	/** @name Aliases */
	/** @{ */
	public:
		using OptionMap = std::map<std::string, AbstractOption&>;
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractPreference(const std::string section_name, std::initializer_list<std::pair<const std::string, AbstractOption&>> map);
		virtual ~AbstractPreference() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		const std::string _section_name;
		const AbstractPreference::OptionMap _map;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
	/** @} */
		
	/** @name Converters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const std::string& getSectionName() const;
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		AbstractPreference::OptionMap::const_iterator cbegin();
		AbstractPreference::OptionMap::const_iterator cend();
		AbstractPreference::OptionMap::const_iterator find(AbstractPreference::OptionMap::key_type key);
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
