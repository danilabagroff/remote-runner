/**
 @file CensoredBuffer.hpp
 @date 10.03.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_Net_Buffer_CensoredBuffer_hpp
#define DrWeb_RemoteRunner_Core_Net_Buffer_CensoredBuffer_hpp

#include "../AbstractBuffer.hpp"

#include <vector>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class CensoredBuffer : public AbstractBuffer
	{
	/** @name Constants */
	/** @{ */
	public:
		static const unsigned short Fuse;
		static const unsigned short Batch;
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		CensoredBuffer(const std::string watermark);
		CensoredBuffer();
		virtual ~CensoredBuffer() = default;
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
		const std::string _watermark;
		
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
