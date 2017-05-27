/**
 @file FlexibleBuffer.hpp
 @date 10.03.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Buffer_FlexibleBuffer_hpp
#define DrWeb_RemoteRunner_Core_Net_Buffer_FlexibleBuffer_hpp

#include "../AbstractBuffer.hpp"

#include <vector>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	
	//@todo Нужен оверрайд overflow() чтобы принимать данные сверх текущего размера через operator<<
	
	class FlexibleBuffer : public AbstractBuffer
	{
	/** @name Constants */
	/** @{ */
	/** @} */
	
	/** @name Constructors */
	/** @{ */
	public:
		FlexibleBuffer();
		FlexibleBuffer(const FlexibleBuffer&) = delete;
		virtual ~FlexibleBuffer() = default;
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
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	protected:
		virtual std::basic_streambuf<char>::int_type overflow(std::basic_streambuf<char>::int_type c) override;
		virtual std::streamsize xsputn(const char_type* sequence, std::streamsize count) override;
		
	public:
		virtual void preserve() final;
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
