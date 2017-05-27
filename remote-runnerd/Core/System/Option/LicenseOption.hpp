/**
 @file LicenseOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_LicenseOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_LicenseOption_hpp

#include "../AbstractOption.hpp"

#include <cstdint>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class LicenseOption : public AbstractOption
	{
	/** @name Classes */
	/** @{ */
	public:
		enum class Type : std::uint8_t
		{
			Unknown = 0,
			Debug = 10,
			Test = 11,
			Demo = 50,
			Server = 100,
			Key = 150,
			Dongle = 200
		};
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		LicenseOption(LicenseOption::Type type = LicenseOption::Type::Key);
		virtual ~LicenseOption() = default;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		LicenseOption::Type _type;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const LicenseOption::Type& getType() const;
	/** @} */
	};
} } } }

#endif
