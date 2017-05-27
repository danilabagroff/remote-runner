/**
 @file SwitchOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_SwitchOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_SwitchOption_hpp

#include "../AbstractOption.hpp"

#include "../../LogRegister.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class SwitchOption : public AbstractOption
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		SwitchOption(const bool onoff = false);
		virtual ~SwitchOption() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		bool _onoff;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
	/** @} */

	/** @name Getters */
	/** @{ */
	public:
		const bool& getState() const;
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool isOn() const;
	/** @} */
	};
} } } }

#endif
