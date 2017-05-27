/**
 @file ExceptionProvoker.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_ExceptionProvoker_hpp
#define DrWeb_RemoteRunner_Core_ExceptionProvoker_hpp

#include <sstream>
#include <string>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	template <typename E>
	class ExceptionProvoker
	{
	/** @name Constructors */
	/** @{ */
	public:
		ExceptionProvoker()
		{

		};
		
		ExceptionProvoker(const ExceptionProvoker &e)
		:
			_payload(e._payload)
		{
			
		};

		~ExceptionProvoker() noexcept
		{

		};
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		E _payload;
	/** @} */

	/** @name Getters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Templates */
	/** @{ */
	public:
		template<typename T>
		E& operator<<(const T &t)
		{
			_payload << t;

			return _payload;
		}
	/** @} */
	};
} } }

#endif
