/**
 @file AbstractPayload.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_Net_AbstractPayload_hpp
#define DrWeb_RemoteRunner_Core_Net_AbstractPayload_hpp

#include "AbstractPayloadAdapter.hpp"

#include <queue>
#include <sstream>
#include <initializer_list>

/*
#include <strstream>
#include <iostream>
*/

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	class AbstractPayload
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractPayload(std::initializer_list<std::shared_ptr<AbstractPayloadAdapter>> list = {});
		virtual ~AbstractPayload();
		
		AbstractPayload& operator=(const AbstractPayload&) = delete;
		AbstractPayload(const AbstractPayload&) = delete;
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::queue<std::shared_ptr<AbstractPayloadAdapter>> _queue;
		
	protected:
		const bool _selfmade;
		/// @todo Заменить на iostream(FlexibleBuffer)
		std::stringstream _payload;
	/** @} */
		
	/** @name Procedures */
	/** @{ */
	public:
		virtual void feed(std::ostream& stream);  /// < Выгрузить текущее состояние в переданный std::ostream
		virtual bool consume(FlexibleBuffer& buffer) final; /// < Забрать из буффера необходимые данные
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		virtual bool isLoaded() const;
	/** @} */
	};
} } } }

#endif
