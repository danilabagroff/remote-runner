/**
 @file AbstractPayload.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "AbstractPayload.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	AbstractPayload::AbstractPayload(std::initializer_list<std::shared_ptr<AbstractPayloadAdapter>> list)
	:
		_queue(list),
		_selfmade(list.size() <= 0),
		_payload(std::ios::binary|std::ios::in|std::ios::out)
	{
		if (!_queue.empty()) {
			_queue.front()->init();
		}
	}
	
	AbstractPayload::~AbstractPayload()
	{

	}
	
	void AbstractPayload::feed(std::ostream& stream)
	{
		/// @xxx Такое копирование работает через overflow(), т.е. побайтово...
		stream << _payload.rdbuf();
	}
	
	bool AbstractPayload::consume(FlexibleBuffer& buffer)
	{
		// Пока есть данные в буффере и есть адаптер в очереди...
		while (!_queue.empty() && !buffer.isEmpty()) {
			// Поглощаем буффер(или его часть) текушем адаптером(PayloadAdapter) полезной нагрузки
			// Если адаптер накопил необходимое(AbstractBuffer::isComplete) количество данных
			while (_queue.front()->absorb(buffer)) {
				// Нужно запустить в работу следующий адаптер убрав при этом из очереди текущий
				_queue.pop();
				
				// Если адаптеры закончились, то запрос сформирован полностью
				if (_queue.empty()) {
					return true;
				}
				
				// Под инициализацией адаптера понимается прежде всего отложенное создание внутренних буфферов.
				_queue.front()->init();
			}
		}

		// Если адпатперов в очереди не осталось — накопление необходимых данных завершено
		return _queue.empty();
	}
	
	bool AbstractPayload::isLoaded() const
	{
		return (false == _selfmade && _queue.empty());
	}
} } } }
