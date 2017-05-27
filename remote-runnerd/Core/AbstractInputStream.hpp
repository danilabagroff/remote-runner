/**
 @file AbstractInputStream.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_AbstractInputStream_hpp
#define DrWeb_RemoteRunner_Core_AbstractInputStream_hpp

#include "AbstractStream.hpp"

#include "../Wand/Type.hpp"
#include "../Wand/Hash.hpp"
#include <istream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class AbstractInputStream : public AbstractStream
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractInputStream(std::istream& stream);
		virtual ~AbstractInputStream() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	protected:
		std::istream& _stream;
		std::size_t _length;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		std::istream& getStream();
		const std::size_t getPosition() const;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	protected:
		virtual const unsigned char readByte() final;
		virtual const std::string readBytes(long length) final;

	public:
		virtual const std::uint8_t readMarker() final;
		virtual const std::uint16_t readType() = 0;
		virtual const std::int64_t readId() = 0;
		virtual const std::uint32_t readSize() = 0;
		virtual const std::uint64_t readIndex() = 0;
		virtual const std::string readBlob() = 0;
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
		virtual void operator>>(std::uint8_t& value) final;

		virtual void operator>>(std::string& value) = 0;
		virtual void operator>>(std::uint16_t& value) = 0;
		virtual void operator>>(std::int16_t& value) = 0;
		virtual void operator>>(std::uint32_t& value) = 0;
		virtual void operator>>(std::int32_t& value) = 0;
		virtual void operator>>(std::uint64_t& value) = 0;
		virtual void operator>>(std::int64_t& value) = 0;
		virtual void operator>>(double& value) = 0;
		virtual void operator>>(bool& value) = 0;
		virtual void operator>>(std::chrono::system_clock::time_point& value) = 0;
	/** @} */
	};
} } }

#endif
