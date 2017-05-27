/**
 @file Exception.hpp
 @date 24.02.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_Net_Exception_hpp
#define DrWeb_RemoteRunner_Core_Net_Exception_hpp

#include "../AbstractException.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class Exception : public AbstractException
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		Exception() = default;
		virtual ~Exception() = default;
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
	public:
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
		template<typename T>
		Exception& operator<<(const T &t)
		{
			flush(t);
			
			return *this;
		}
	/** @} */
	};
} } } }

#endif
