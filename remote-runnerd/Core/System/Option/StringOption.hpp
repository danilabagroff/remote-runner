/**
 @file StringOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_StringOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_StringOption_hpp

#include "../AbstractOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class StringOption : public AbstractOption
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		StringOption(const std::string& string);
		virtual ~StringOption() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::string _string;
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
		const std::string& getString() const;
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
