/**
 @file LimitedBuffer.hpp
 @date 10.03.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Buffer_LimitedBuffer_hpp
#define DrWeb_RemoteRunner_Core_Net_Buffer_LimitedBuffer_hpp

#include "../AbstractBuffer.hpp"

#include <vector>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class LimitedBuffer : public AbstractBuffer
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		LimitedBuffer(const std::size_t limit);
		virtual ~LimitedBuffer() = default;
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
		
	protected:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */		
	protected:
		virtual std::streamsize xsputn(const char_type* sequence, std::streamsize count) override;
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
