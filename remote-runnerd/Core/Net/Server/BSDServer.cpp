/**
 @file BSDServer.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "BSDServer.hpp"

#include "../Socket/ClientSocket.hpp"
#include "../Log.hpp"

#include <sys/event.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	Server::Server(std::unique_ptr<ServerSocket> socket)
	:
		AbstractServer(std::move(socket))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}

	bool Server::run()
	{
		if (!AbstractServer::run()) {
			return false;
		}

		// Создаем очередь
		int kq = kqueue();
		if (kq <= 0) {
			LogRegister<Net::Log>::Fatal("Server > Network monitor based on kqueue(", kq, ") has not been initialized: ", errno);
			return false;
		}
		LogRegister<Net::Log>::Notice("Server > Network monitor based on kqueue(", kq, ") has been successfully initialized");
		
		struct kevent event_set[5];
		EV_SET(&event_set[0], _socket->getHandle(), EVFILT_READ, EV_ADD, 0, 0, NULL);
		EV_SET(&event_set[1], SIGINT, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
		EV_SET(&event_set[2], SIGHUP, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
		EV_SET(&event_set[3], SIGTERM, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
		EV_SET(&event_set[4], SIGQUIT, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
		
		// Очередь не создалась — тушим свет
		if (kevent(kq, event_set, 5, NULL, 0, NULL) == -1) {
			LogRegister<Net::Log>::Fatal("Server > Network monitor based on kqueue(", kq, ") has not been initialized: ", errno);

			return false;
		}

		// "За раз" обрабатываем не больше 32 событий
		struct kevent event_list[32];

		// Шаблон для оформления подписки/отписки клиентских соединений
		struct kevent event_template[2];

		// Поехали!
		while (_online) {
			// Блокируем до тех пор, пока что-нибудь не произойдет
			int count = kevent(kq, NULL, 0, event_list, 32, NULL);
			
			// Не смогли получить хоть какие-то события
			if (count < 0) {
				int e(errno);
				if (e != EINTR) {
					LogRegister<Net::Log>::Fatal("Server > Error occured: ", e);
					return false;
				}
			}
			
			// Обработаем все полученные события
			for (int e = 0; e < count; e++) {
				LogRegister<Net::Log>::Notice("Server * Looping kqueue events: ", event_list[e].flags);

				if (event_list[e].filter == EVFILT_SIGNAL) { /// < Перехваченный сигнал
					if (onSignal(event_list[e].ident)) {
						LogRegister<Net::Log>::Warning("Server * Stopping...");
						_online = false;
						break;
					}
					LogRegister<Net::Log>::Warning("Server * Resuming...");
					continue;
				}
				
				if (event_list[e].filter == EVFILT_TIMER) { /// < Таймер
					PollMap::iterator* iterator((PollMap::iterator*)event_list[e].udata);
					LogRegister<Net::Log>::Notice("Server * Validating connection(", iterator, ")...");					
					
					if (!assert(*iterator)) {
						LogRegister<Net::Log>::Notice("Server * Assetion failed, removing connection(", iterator, ")...");
						/// Удаляем из пула
						if (!reject(*iterator)) {
							LogRegister<Net::Log>::Error("Server > Couldn't find handle(", event_list[e].ident, ") in the pool");
						}
						delete iterator;

						EV_SET(&event_template[0], event_list[e].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
						EV_SET(&event_template[1], event_list[e].ident, EVFILT_TIMER, EV_DELETE, 0, 0, NULL);
						if (kevent(kq, event_template, 1, NULL, 0, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not register the kevent in the eventlist: ", strerror(errno));
						}
					}

					continue;
				}

				if (event_list[e].flags & EV_ERROR) { /// < Егорины ашипки
					PollMap::iterator* iterator((PollMap::iterator*)event_list[e].udata);

					LogRegister<Net::Log>::Error("Server > An unexpected error on connection(", event_list[e].ident, ") has occurred: ", strerror(event_list[e].data));

					// Удалем из списка наблюдаемых
					EV_SET(&event_template[0], event_list[e].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
					EV_SET(&event_template[1], event_list[e].ident, EVFILT_TIMER, EV_DELETE, 0, 0, NULL);
					if (kevent(kq, event_template, 2, NULL, 0, NULL) < 0) {
						LogRegister<Net::Log>::Error("Server > Could not unregister the kevent in the eventlist: ", strerror(errno));
					}
					// Удаляем из хэш-таблицы
					if (!reject(*iterator)) {
						LogRegister<Net::Log>::Error("Server > Couldn't remove connection(", iterator, ") from the pool");
					}
					delete iterator;

					continue;
				}
				
				if (event_list[e].flags & EV_EOF) { /// < Кто-то отцепился
					PollMap::iterator* iterator((PollMap::iterator*)event_list[e].udata);
					LogRegister<Net::Log>::Notice("Server * Removing connection(", iterator, ")...");
					
					// Удалем из списка наблюдаемых
					EV_SET(&event_template[0], event_list[e].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
					EV_SET(&event_template[1], event_list[e].ident, EVFILT_TIMER, EV_DELETE, 0, 0, NULL);
					if (kevent(kq, event_template, 2, NULL, 0, NULL) < 0) {
						LogRegister<Net::Log>::Error("Server > Could not unregister the kevent from the eventlist: ", strerror(errno));
					}
					// Удаляем из хэш-таблицы
					if (!reject(*(PollMap::iterator*)event_list[e].udata)) {
						LogRegister<Net::Log>::Error("Server > Couldn't remove connection(", iterator, ") from the poll");
					}
					delete iterator;
				} else if (_socket->getHandle() == event_list[e].ident) { /// < Кто-то новенький на главном сокете
                    int handle(0);
                    PollMap::iterator* iterator(new PollMap::iterator(accept(handle)));
					LogRegister<Net::Log>::Notice("Server * Accepting new connection(", iterator, ")...");
					
					if (*iterator == _poll.end()) {
						LogRegister<Net::Log>::Error("Server > Could not emplace connection in the poll");
						continue;
					}
					
					LogRegister<Net::Log>::Notice("Server > Connection(", iterator, ") has been successfully emplaced in the poll");

					// Добавляем в список наблюдаемых
					EV_SET(&event_template[0], handle, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, iterator);
					/// @todo После соединения должно что-то обязательно придти в течение 10000ms (брать из конфига)
					EV_SET(&event_template[1], handle, EVFILT_TIMER, EV_ADD | EV_ONESHOT, 0, 10000, iterator);
					if (kevent(kq, event_template, 2, NULL, 0, NULL) < 0) {
						/// Удаляем из пула
						if (!reject(*iterator)) {
							LogRegister<Net::Log>::Error("Server > Couldn't find connection(", iterator, ") in the poll");
						}
						delete iterator;
						LogRegister<Net::Log>::Error("Server > Could not register the kevent in the eventlist: ", strerror(errno));
					}
				} else if (event_list[e].flags & EVFILT_READ) { /// < Что-то пришло на сокет
					PollMap::iterator* iterator((PollMap::iterator*)event_list[e].udata);
					LogRegister<Net::Log>::Notice("Server > Data(", event_list[e].data, " bytes) on connection(", event_list[e].ident, ") is avaliable for reading");
					if (!receive(*iterator)) {
						LogRegister<Net::Log>::Error("Server > Couldn't fetch connection (", iterator, ") from the poll");
					} else {
						/// @xxx Так как соединение уже валидированно текущим чтением возникает вопрос в необходимости удалять ранее установленный, но еще не сработавший таймер
						/// Уверенности в необходимости этого нет, так как EV_SET в данном случае перезапишет ранее установленный kevent?
						// EV_SET(&event_template[0], event_list[e].ident, EVFILT_TIMER, EV_DELETE, 0, 0, NULL);
						
						/// @todo После очередного чтения проверим соединение через 50000ms (брать из конфига)
						EV_SET(&event_template[0], event_list[e].ident, EVFILT_TIMER, EV_ADD | EV_ONESHOT, 0, 50000, iterator);
						if (kevent(kq, event_template, 1, NULL, 0, NULL) < 0) {
							/// Удаляем из пула
							if (!reject(*iterator)) {
								LogRegister<Net::Log>::Error("Server > Couldn't find connection(", event_list[e].ident, ") in the poll");
							}
							delete iterator;
							LogRegister<Net::Log>::Error("Server > Could not register the kevent in the eventlist: ", strerror(errno));
						}
					}
				} else {
					LogRegister<Net::Log>::Warning("Server > Unexpected event(", event_list[e].flags, ") on connection(", event_list[e].ident, ")");
				}
			}
		}
		
		close(kq);

		return true;
	}

	Server::PollMap::iterator Server::accept(int& socket)
	{
		const std::shared_ptr<Connection> connection(new Connection(_socket->accept()));

		if (connection->getDescriptor() <= 0) {
			LogRegister<Net::Log>::Error("Server > Connection has been refused");
			socket = 0;
			return _poll.end();
		}
		socket = connection->getDescriptor();

		Server::PollMap::iterator retval;
		std::tie(retval, std::ignore) = _poll.emplace(connection->getDescriptor(), std::make_shared<Transmission>(makeProxy(connection)));

		return retval;
	}

	bool Server::reject(Server::PollMap::iterator iterator)
	{
		if (iterator == _poll.end()) {
			LogRegister<Net::Log>::Error("Server > Invalid poll iterator");
			return false;
		}

		LogRegister<Net::Log>::Debug("Server * Socket(", iterator->first, ") is going to be removed from the poll...");
		iterator->second->async(TransmissionRoutine::Drop);
		_poll.erase(iterator);

		return true;
	}

	bool Server::receive(Server::PollMap::iterator iterator)
	{
		if (iterator == _poll.end()) {
			LogRegister<Net::Log>::Error("Server > Invalid poll iterator");
			return false;
		}

		iterator->second->async(TransmissionRoutine::Transfer);
		LogRegister<Net::Log>::Debug("Server > Read has been run asynchronously on the socket(", iterator->first, ")");

		return true;
	}

	bool Server::assert(Server::PollMap::iterator iterator)
	{
		if (iterator == _poll.end()) {
			LogRegister<Net::Log>::Error("Server > Invalid poll iterator");
			return false;
		}

		LogRegister<Net::Log>::Debug("Server * Socket(", iterator->first, ") is going to be validated...");
		iterator->second->async(TransmissionRoutine::Validation);

		return true;
	}

	bool Server::onSignal(unsigned short int sig)
	{
		switch (sig) {
			case SIGQUIT:
				return onSignal(AbstractServer::Signal::Quit);
				break;
			case SIGINT:
				return onSignal(AbstractServer::Signal::Interruption);
				break;
			case SIGHUP:
				return onSignal(AbstractServer::Signal::HangUp);
				break;
			case SIGTERM:
				return onSignal(AbstractServer::Signal::Termination);
				break;
			default:
				return onSignal(AbstractServer::Signal::Unknown);
		}
	}
} } } }
