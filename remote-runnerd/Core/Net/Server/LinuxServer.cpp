/**
 @file LinuxServer.cpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#include "LinuxServer.hpp"

#include "../Socket/ClientSocket.hpp"
#include "../Log.hpp"

#include <string.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <signal.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	Server::Server(std::unique_ptr<ServerSocket> socket)
	:
		AbstractServer(std::move(socket))
	{
		sigemptyset(&_signal_set);
		sigaddset(&_signal_set, SIGINT);
		sigaddset(&_signal_set, SIGHUP);
		sigaddset(&_signal_set, SIGTERM);
		sigaddset(&_signal_set, SIGQUIT);

		pthread_sigmask(SIG_BLOCK, &_signal_set, NULL);
	}

	bool Server::run()
	{
		/// @xxx Если pthread_sigmask не удался, то: LogRegister<Net::Log>::Fatal("Server > Signal mask has not been initialized: ", errno);
		
		if (!AbstractServer::run()) {
			return false;
		}

		int signal_handle = signalfd(-1, &_signal_set, 0);
		if (signal_handle < 0) {
			LogRegister<Net::Log>::Fatal("Server > Signal handle has not been initialized: ", errno);
			return false;
		}

		struct epoll_event event_set;
		int ep = epoll_create1(0);
		if (ep <= 0) {
			LogRegister<Net::Log>::Fatal("Server > Network monitor epoll(", ep, ") has not been initialized: ", errno);
			return false;
		}
		LogRegister<Net::Log>::Notice("Server > Network monitor epoll(", ep, ") has been successfully initialized");

		event_set.data.fd = _socket->getHandle();
		event_set.events = EPOLLIN | EPOLLET;
		if (epoll_ctl(ep, EPOLL_CTL_ADD, _socket->getHandle(), &event_set) == -1) {
			LogRegister<Net::Log>::Fatal("Server > Network monitor epoll(", ep, ") has not been initialized: ", errno);

			return false;
		}

		event_set.data.fd = signal_handle;
		event_set.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		if (epoll_ctl(ep, EPOLL_CTL_ADD, signal_handle, &event_set) == -1) {
			LogRegister<Net::Log>::Fatal("Server > Network monitor epoll(", ep, ") has not been initialized: ", errno);

			return false;
		}

		// "За раз" обрабатываем не больше 32 событий
		struct epoll_event event_list[32];

		// Шаблон для оформления подписки/отписки клиентских соединений
		struct epoll_event event_template;
		
		// Поехали!
		while (_online) {
			// Блокируем до тех пор, пока что-нибудь не произойдет
			int count = epoll_wait(ep, event_list, 32, -1);

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
				LogRegister<Net::Log>::Notice("Server * Looping epoll events: ", event_list[e].events);

				if (event_list[e].events & EPOLLERR) { /// < Егорины ашипки
					PollMap::iterator s(_socket_map.find(event_list[e].data.fd));
					if (_socket_map.end() == s) {
						LogRegister<Net::Log>::Error("Server > Couldn't find requested socket(", event_list[e].data.fd, ")");
						continue;
					}
					const int socket_handle(s->first);
					LogRegister<Net::Log>::Error("Server > An unexpected error on socket(", socket_handle, ") has occurred: "/*, strerror(event_list[e].data)*/);

					/// Удалем из списка наблюдаемых
					if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
						LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from the epoll: ", strerror(errno));
					}

					PollMap::iterator t(_timer_map.find(event_list[e].data.fd));
					if (_timer_map.end() == t) {
						LogRegister<Net::Log>::Error("Server > Couldn't find timer for requested socket(", event_list[e].data.fd, ")");
					} else {
						const int timer_handle(t->first);
						/// Удалем из списка наблюдаемых
						if (epoll_ctl(ep, EPOLL_CTL_DEL, timer_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the timer event from the epoll: ", strerror(errno));
						}
						close(timer_handle);
						LogRegister<Net::Log>::Debug("Server > Timer(", timer_handle, ") has been removed from the map");
					}

					/// Удаляем из хэш-таблицы
					_socket_map.erase(s);
					LogRegister<Net::Log>::Debug("Server > Socket(", socket_handle, ") has been removed from the map");

					continue;
				}

				if (event_list[e].data.fd == signal_handle) { /// < Сигнал от ядра
					struct signalfd_siginfo signal_info;

					if (::read(signal_handle, &signal_info, sizeof(signal_info)) != sizeof(signal_info)) {
						LogRegister<Net::Log>::Error("Server > Couldn't fetch signal info");
						LogRegister<Net::Log>::Warning("Server * Stopping...");
						/// @xxx И что?
						_online = false;
						break;
					}

					if (onSignal(signal_info.ssi_signo)) {
						LogRegister<Net::Log>::Warning("Server * Stopping...");
						_online = false;
						break;
					}
					LogRegister<Net::Log>::Warning("Server * Resuming...");
					continue;
				}

				if (_socket->getHandle() == event_list[e].data.fd && event_list[e].events & EPOLLIN) {  /// < Кто-то новенький на главном сокете
					/// Принимаем соединение и создаем клиентский сокет
					const std::shared_ptr<Connection> connection(new Connection(_socket->accept()));

					if (connection->getDescriptor() <= 0) {
						LogRegister<Net::Log>::Error("AbstractServer > Connection has been refused");
						continue;
					}
					const int socket_handle(connection->getDescriptor());

					/// Cоздаем прокси
					std::shared_ptr<AbstractProxy> proxy(makeProxy(connection));

					/// Добавляем сокет в список наблюдаемых
					event_template.data.fd = socket_handle;
					event_template.events = EPOLLIN | EPOLLRDHUP | EPOLLET /*|| EPOLLONESHOT*/ ;
					if (epoll_ctl(ep, EPOLL_CTL_ADD, socket_handle, &event_template) < 0) {
						LogRegister<Net::Log>::Error("Server > Could not add socket event to the epoll: ", strerror(errno));
						continue;
					}

					/// Создаем таймер
					const int timer_handle = timerfd_create(CLOCK_MONOTONIC, 0);
					if (timer_handle == -1) {
						LogRegister<Net::Log>::Error("Server > Could not create the timer: ", strerror(errno));

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
						}
						continue;
					}

					/// Устаналиваем время
					if (!setTimer(timer_handle)) {
						LogRegister<Net::Log>::Error("Server > Could not set timeout: ", strerror(errno));

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
						}

						/// Закрываем таймер
						close(timer_handle);
						continue;
					}

					/// Добавляем событие на прослушивание таймера
					event_template.events = EPOLLIN;
					event_template.data.fd = timer_handle;
					if (epoll_ctl(ep, EPOLL_CTL_ADD, timer_handle, &event_template) == -1) {
						LogRegister<Net::Log>::Error("Server > Could not add timer event to the epoll: ", strerror(errno));

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
						}

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, timer_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the timer event from epoll: ", strerror(errno));
						}

						/// Закрываем таймер
						close(timer_handle);
						continue;
					}

					std::shared_ptr<Transmission> coroutine(new Transmission(proxy));

					PollMap::iterator s(_socket_map.end());
					std::tie(s, std::ignore) = _socket_map.emplace(socket_handle, std::make_pair(timer_handle,  coroutine));
					if (s == _socket_map.end()) {
						LogRegister<Net::Log>::Error("Server > Could not emplace connection(", timer_handle, ") in the map");
						continue;

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
						}

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, timer_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the timer event from epoll: ", strerror(errno));
						}

						close(timer_handle);
						continue;
					}
					LogRegister<Net::Log>::Notice("Server > Connection(", socket_handle, ") has been successfully emplaced in the map");

					PollMap::iterator t(_timer_map.end());
					std::tie(t, std::ignore) = _timer_map.emplace(timer_handle, std::make_pair(socket_handle, coroutine));
					if (t == _timer_map.end()) {
						LogRegister<Net::Log>::Error("Server > Could not emplace timer in the map");

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
						}

						/// Удаляем событие
						if (epoll_ctl(ep, EPOLL_CTL_DEL, timer_handle, NULL) < 0) {
							LogRegister<Net::Log>::Error("Server > Could not unregister the timer event from epoll: ", strerror(errno));
						}

						/// Закрываем таймер
						close(timer_handle);
						_socket_map.erase(s);
						continue;
					}
					LogRegister<Net::Log>::Notice("Server > Timer(", timer_handle, ") has been successfully emplaced in the map");
				} else if (event_list[e].events & EPOLLRDHUP) { /// < Кто-то отцепился
					PollMap::iterator s(_socket_map.find(event_list[e].data.fd));
					if (_socket_map.end() == s) {
						LogRegister<Net::Log>::Error("Server > Couldn't find requested connection(", event_list[e].data.fd, ")");
						continue;
					}
					const int socket_handle(s->first);
					const int timer_handle(s->second.first);
					PollMap::iterator t(_timer_map.find(timer_handle));
					if (_timer_map.end() == t) {
						LogRegister<Net::Log>::Error("Server > Couldn't find requested timer(", timer_handle, ")");
					} else {
						/// Удаляем из хэш-таблицы
						_timer_map.erase(t);
						LogRegister<Net::Log>::Debug("Server > Timer(", timer_handle, ") has been removed from the map");
					}

					/// Удаляем из списка наблюдаемых
					if (epoll_ctl(ep, EPOLL_CTL_DEL, socket_handle, NULL) < 0) {
						LogRegister<Net::Log>::Error("Server > Could not unregister the epoll event in the eventlist: ", strerror(errno));
					}

					/// Удаляем из списка наблюдаемых
					if (epoll_ctl(ep, EPOLL_CTL_DEL, timer_handle, NULL) < 0) {
						LogRegister<Net::Log>::Error("Server > Could not unregister the epoll event in the eventlist: ", strerror(errno));
					}
					close(timer_handle);

					/// Удаляем из хэш-таблицы
					_socket_map.erase(s);
					LogRegister<Net::Log>::Debug("Server > Socket(", socket_handle, ") has been removed from the map");
				} else if (event_list[e].events & EPOLLIN) { // Что-то пришло на сокет или сработал таймер
					LogRegister<Net::Log>::Notice("Server > Data on handle(", event_list[e].data.fd, ") is available for reading");
					PollMap::iterator s(_socket_map.find(event_list[e].data.fd));

					if (_socket_map.end() != s) {
						s->second.second->async(TransmissionRoutine::Transfer);
						LogRegister<Net::Log>::Debug("Server > Read has been run asynchronously on the handle ", s->first);

						const int timer_handle(s->second.first);
						if (!setTimer(timer_handle)) {
							LogRegister<Net::Log>::Error("Server > Could not set timeout: ", strerror(errno));

							/// Удаляем событие
							if (epoll_ctl(ep, EPOLL_CTL_DEL, timer_handle, NULL) < 0) {
								LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
							}

							/// Закрываем таймер
							close(timer_handle);

							/// Удаляем из пула
							PollMap::iterator t(_timer_map.find(timer_handle));
							if (_timer_map.end() == t) {
								LogRegister<Net::Log>::Error("Server > Couldn't find requested timer(", timer_handle, ")");
							} else {
								_timer_map.erase(t);
							}
						}
					} else {
						PollMap::iterator t(_timer_map.find(event_list[e].data.fd));
						if (_timer_map.end() != t) {
							std::uint64_t value;
							read(t->first, &value, 8);
							t->second.second->async(TransmissionRoutine::Validation);
							LogRegister<Net::Log>::Debug("Server > Validation has been run asynchronously on the handle ", t->first);

							setTimer(event_list[e].data.fd, 50);
						} else {
							LogRegister<Net::Log>::Error("Server > Couldn't find requested timer handle(", event_list[e].data.fd, ") in the map");

							/// Останавливаем таймер
							setTimer(event_list[e].data.fd, 0);

							/// Удаляем событие
							if (epoll_ctl(ep, EPOLL_CTL_DEL, event_list[e].data.fd, NULL) < 0) {
								LogRegister<Net::Log>::Error("Server > Could not unregister the socket event from epoll: ", strerror(errno));
							}

							/// Закрываем таймер
							close(event_list[e].data.fd);
							continue;
						}
					}
				} else {
					LogRegister<Net::Log>::Warning("Server > Unexpected epoll event(", event_list[e].events, ") on handle ", event_list[e].data.fd);
				}
			}
		}
		
		close(ep);
		close(signal_handle);

		return true;
	}

	bool Server::setTimer(const int handle, const int timeout)
	{
		struct itimerspec ts;
		ts.it_interval.tv_sec = 0;
		ts.it_interval.tv_nsec = 0;
		ts.it_value.tv_sec = timeout;
		ts.it_value.tv_nsec = 0;

		/// Устаналиваем время
		if (timerfd_settime(handle, 0, &ts, NULL) < 0) {
			return false;
		}

		return true;
	}

	bool Server::onSignal(uint32_t sig)
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
