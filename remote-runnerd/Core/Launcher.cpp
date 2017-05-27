/**
 @file Launcher.cpp
 @date 11.06.15

 @author Daniil A Megrabyan
*/

#include "Launcher.hpp"

#include "Net/Response/TelnetLaunchResponse.hpp"
#include "Net/Response/TelnetApplicationTimeoutResponse.hpp"

#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../Wand/String.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core {
	Launcher::Launcher(std::string filepath, unsigned long timeout)
	:
		_filepath(filepath),
		_timeout(timeout)
	{
		reload();
	}
	
	Launcher::~Launcher()
	{

	}
	
	bool Launcher::exec(const std::string command, std::weak_ptr<Net::Connection> connection)
	{
		std::shared_ptr<Net::Connection> c(connection.lock());
		if (nullptr == c) {
			return false;
		}

		if (command.empty() || command.compare("\n") == 0) {
			/// Пропускаем мимо ушей
			return false;
		}
		
		if (!isAllowed(command)) {
			c->push(std::make_shared<Net::TelnetLaunchResponse>("Requested application is not permitted"));
			return false;
		}
		
		int pp[2];
		if (pipe(pp) < 0) {
			return false;
		}
		
		pid_t pid(0);
		if ((pid = fork()) < 0) {
			/// @todo
			return false;
		} else if (pid == 0) {
			/// Разбиваем аргументы
			std::vector<std::string> vector(wand::explode<std::vector, std::string>(command, " "));

			/// Тряхнем стариной
			const char** argv = new const char*[vector.size() + 1];
			argv[vector.size()] = NULL;
			for (int i=0; i<vector.size(); i++) {
				argv[i] = vector[i].c_str();
			}
			
			/// В дочернем процессе будем только писать
			close(pp[0]);
			
			/// Закрываем stdout
			close(1);
			/// 
			dup(pp[1]);

			execv(argv[0], (char**)argv);
			_exit(EXIT_FAILURE);
		} else {
			/// В дочернем процессе будем только читать
			close(pp[1]);
			
			std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
			pid_t child_pid(0);
			/// Ждем пока потомок завершится
			while ((child_pid = waitpid(pid, NULL, WNOHANG)) != pid) {
				if (-1 == child_pid) {
					/// @todo
					return false;
				} else if (0 == child_pid) {
					/// Процесс еще не завершился, проверим таймаут и пошлем kill в случае превышения
					if (std::chrono::system_clock::now() - start >= _timeout) {
						c->push(std::make_shared<Net::TelnetApplicationTimeoutResponse>());
						if (kill(pid, SIGKILL) != 0) {
							return false;
						}
						if (waitpid(pid, NULL, 0) == -1) {
							/// @todo
							return false;
						}
						break;
					}
				}
			}

			std::string buffer("");
			char byte;
			while(read(pp[0], &byte, 1) == 1) {
				buffer += byte;
			}
			close(pp[0]);

			if (!buffer.empty()) {
				c->push(std::make_shared<Net::TelnetLaunchResponse>(buffer));
			}
		}
		
		return true;
	}
	
	bool Launcher::reload()
	{
		std::fstream stream;
		stream.open(_filepath, std::ios_base::in);
		
		if (!stream.is_open()) {
			return false;
		}
		
		/// @note В начало файла
		stream.clear();
		stream.seekg(std::ios_base::seekdir::beg);

		/// @note Race condition safety
		std::lock_guard<std::mutex> lock(_mutex);
		_access_set.clear();
		
		/// @note Фигачим
		std::string line;
		while (!std::getline(stream, line).eof()) {
			_access_set.insert(line);
		}

		return true;
	}
	
	bool Launcher::isAllowed(const std::string& command) const
	{
		/// @note Race condition safety
		std::lock_guard<std::mutex> lock(_mutex);
		
		return _access_set.find(command) == _access_set.end() ? false : true;
	}
	
} } }
