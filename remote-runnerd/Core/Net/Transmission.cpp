/**
 @file Transmission.cpp
 @date 05.05.15

 @author Daniil A Megrabyan
 */

#include "Transmission.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	Transmission::Transmission(const std::shared_ptr<AbstractProxy> proxy)
	:
		_proxy(proxy),
		_connection(proxy->getConnection()),
		wand::coroutine<bool, TransmissionRoutine>(false)
	{

	}
	
	bool Transmission::co(TransmissionRoutine argument)
	{
		switch (argument) {
			case TransmissionRoutine::Transfer:
				return transfer();
				break;
			case TransmissionRoutine::Validation:
				return validate();
				break;
			case TransmissionRoutine::Drop:
				return drop();
				break;
			default:
				return false;
		}
	}
	
	bool Transmission::transfer()
	{
		std::shared_ptr<AbstractProxy> proxy(nullptr);
		
		while (nullptr != _proxy) {
			/// Обработаем с помощью прокси данные накопленные в буфере соединения
			proxy = _proxy->transmit();
			if (proxy == _proxy) { /// < Если прокси тот же, значит просто не хватает данных, завершаем вызов корутины
				/// Корутина обслуживающая соединение еще нужна, так как прокси может еще обработать новые данные
				return true;				
			} else { /// < Прокси поменяли, значит если остались данные в буфере соединения нужно их передать на обработку в следующией итерации
				_proxy = proxy;
			}
		}
		
		return true;
	}
	
	bool Transmission::validate()
	{
		if (nullptr == _proxy) {
			return false;
		}
		
		if (_proxy->isValid()) {
			return true;
		}
		
		_connection.reset();
		_proxy.reset();		
		
		return false;
	}
	
	bool Transmission::drop()
	{
		_connection.reset();
		
		if (nullptr == _proxy) {
			return true;
		}
		
		_proxy->dispose();
		
		return true;
	}
} } } }
