/**
 @file AbstractPayloadAdapter.hpp
 @date 13.03.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractPayloadAdapter_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractPayloadAdapter_hpp

#include <istream>
#include <memory>

#include "AbstractBuffer.hpp"
#include "Buffer/FlexibleBuffer.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractPayloadAdapter
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		AbstractPayloadAdapter();
		virtual ~AbstractPayloadAdapter() = default;
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
	protected:
		std::shared_ptr<AbstractBuffer> _buffer;
		std::istream _stream;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool init();
		virtual bool absorb(FlexibleBuffer& buffer) final;
		
	protected:
		virtual void digest() = 0;
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
