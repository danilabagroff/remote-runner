/**
 @file StreamException.hpp
 @date 02.04.16

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_StreamException_hpp
#define DrWeb_RemoteRunner_Core_StreamException_hpp

#include "AbstractException.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class StreamException : public AbstractException
	{
	/** @name Classes */
	/** @{ */
	public:
		enum class Code : std::uint8_t
		{
			Unknown = 0x00,
			StreamWriting = 0x01,
			StreamReading = 0x02
		};
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		StreamException() = default;
		virtual ~StreamException() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		StreamException::Code _code;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		virtual const StreamException::Code& getCode() const;
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
		template<typename T>
		StreamException& operator<<(const T &t)
		{
			flush(t);
			
			return *this;
		}
		
		StreamException& operator<<(StreamException::Code code)
		{
			_code = code;
			
			return *this;
		}
	/** @} */
	};
} } }

#endif
