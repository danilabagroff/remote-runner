/**
 @file AbstractStream.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_AbstractStream_hpp
#define DrWeb_RemoteRunner_Core_AbstractStream_hpp

#include "StreamException.hpp"

#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

namespace DrWeb { namespace RemoteRunner { namespace Core {
	class AbstractStream
	{
	/** @name Constructors */
	/** @{ */
	public:
		virtual ~AbstractStream() = default;
	/** @} */		
	};
} } }

#endif
