/**
 @file Transmission.hpp
 @date 05.05.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Transmission_hpp
#define DrWeb_RemoteRunner_Core_Net_Transmission_hpp

#include "AbstractProxy.hpp"

#include "../../Wand/Coroutine.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	enum class TransmissionRoutine
	{
		Transfer,
		Validation,
		Drop
	};
	
	class Transmission : public wand::coroutine<bool, TransmissionRoutine>
	{
	/** @name Constructors */
	/** @{ */
	public:

	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		Transmission(const std::shared_ptr<AbstractProxy> proxy);
		virtual ~Transmission() = default;
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
		std::shared_ptr<const Connection> _connection;
		std::shared_ptr<AbstractProxy> _proxy;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	protected:
		virtual bool co(TransmissionRoutine argument) override;
		
	private:
		virtual bool transfer();
		virtual bool validate();
		virtual bool drop();
	/** @} */
		
	/** @name States  */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
