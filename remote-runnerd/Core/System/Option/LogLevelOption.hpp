/**
 @file LogLevelOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_LogLevelOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_LogLevelOption_hpp

#include "../AbstractOption.hpp"

#include "../../LogLevel.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class LogLevelOption : public AbstractOption
	{
	/** @name Constructors */
	/** @{ */
	public:
		LogLevelOption(LogLevel level = LogLevel::Warning);
		virtual ~LogLevelOption() = default;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		LogLevel _level;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const LogLevel& getLevel() const;
	/** @} */
	};
} } } }

#endif
