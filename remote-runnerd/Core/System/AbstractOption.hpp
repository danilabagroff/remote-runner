/**
 @file AbstractOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_AbstractOption_hpp
#define DrWeb_RemoteRunner_Core_System_AbstractOption_hpp

#include <istream>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class AbstractOption
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractOption() = default;
		virtual ~AbstractOption() = default;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) = 0;
		virtual bool operator()(const std::string& value) final;
	/** @} */
		
	/** @name Properties */
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
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
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
