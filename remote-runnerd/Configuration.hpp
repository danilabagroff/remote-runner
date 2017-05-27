/**
 @file Configuration.hpp
 @date 11.06.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Configuration_hpp
#define DrWeb_RemoteRunner_Configuration_hpp

#include "Core/System/AbstractPreference.hpp"

#include <fstream>
#include <string>
#include <map>
#include <functional>

namespace DrWeb { namespace RemoteRunner {
	class Configuration
	{
	/** @name Constructors */
	/** @{ */
	public:
		Configuration(std::fstream& stream);
		virtual ~Configuration();
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
		std::fstream& _stream;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		bool load(Core::System::AbstractPreference& preference);
		bool validate(const Core::System::AbstractPreference& preference);
		
		bool open(const std::string filename);
		bool save();
		bool close();
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
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		const bool isOpened() const;
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
} }

#endif
