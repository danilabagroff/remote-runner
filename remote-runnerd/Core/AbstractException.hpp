/**
 @file AbstractException.hpp
 @date 24.02.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_AbstractException_hpp
#define DrWeb_RemoteRunner_Core_AbstractException_hpp

#include "ExceptionProvoker.hpp"

#include <exception>
#include <iostream>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class AbstractException : public std::exception
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractException()
		{
			
		};
		
		virtual ~AbstractException()
		{
			
		};
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::string _message;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual const char* what() const noexcept final
		{
			return _message.c_str();
		};
		
		virtual const std::string& getMessage() const noexcept final
		{
			return _message;
		};
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
		template<typename T>
		void flush(const T &t)
		{
			std::stringstream ss;
			ss << t;
			_message += ss.str();
		};
		
		void flush(std::ostream& (*f)(std::ostream&))
		{
			/// @note Игнорируем переносы строк
		};
	/** @} */
	};
} } }

#endif
