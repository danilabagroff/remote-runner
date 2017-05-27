/**
 @file TimeoutOption.hpp
 @date 26.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_TimeoutOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_TimeoutOption_hpp

#include "../AbstractOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class TimeoutOption : public AbstractOption
	{
	/** @name Constructors */
	/** @{ */
	public:
		TimeoutOption(const unsigned long seconds = 0);
		virtual ~TimeoutOption() = default;
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
		unsigned long _timeout;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const unsigned long& getTimeout() const;
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
