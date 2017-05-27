/**
 @file AbstractBuffer.hpp
 @date 10.03.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractBuffer_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractBuffer_hpp

#include <vector>
#include <memory>
#include <utility>
#include <iostream>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractBuffer : public std::basic_streambuf<char>
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractBuffer();
		AbstractBuffer(const AbstractBuffer&) = delete;
		virtual ~AbstractBuffer() = default;
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
		std::vector<std::basic_streambuf<char>::char_type> _vector;
		bool _complete;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		/**
		 @brief Абсорбирование(перемещение) буфера(или части буфера)
		 @param source Источник из которого необходимая целевому буфера часть будет удалена
		 */
		virtual std::streamsize absorb(AbstractBuffer& source) final;
		
	protected:
		virtual std::basic_streambuf<char>::int_type overflow(std::basic_streambuf<char>::int_type c) override;
		virtual std::streamsize xsputn(const char_type* sequence, std::streamsize count) override;
		virtual std::basic_streambuf<char>::pos_type seekoff(std::basic_streambuf<char>::off_type offset, std::ios_base::seekdir direction, std::ios_base::openmode mode = std::ios_base::out | std::ios_base::in) override;
		virtual std::basic_streambuf<char>::pos_type seekpos(std::basic_streambuf<char>::pos_type position, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override;
		virtual void resize(const std::size_t size) final;
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
		virtual const std::size_t getSize() const final;
		virtual	const std::vector<std::basic_streambuf<char>::char_type>& getVector() const final;
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		virtual const bool isEmpty() final;
		virtual const bool isComplete() const final;
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
