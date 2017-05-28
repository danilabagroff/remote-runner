/**
 @file Runner.cpp
 @date 2017-05-26
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 */

#include "Bootstrap/DaemonBootstrap.hpp"
/*
#include "Bootstrap/HelpBootstrap.hpp"
#include "Bootstrap/VersionBootstrap.hpp"
#include "Bootstrap/TestBootstrap.hpp"
*/

#include <fstream>
#include <utility>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <syslog.h>

enum class BootstrapMode : std::uint8_t {
	Daemon = 'd',
	Test = 't',
	Version = 'v',
	Help = 'h'
};

int main(int argc, char* argv[])
{
	/// Конфигурационный поток
	std::fstream configuration_stream;
	
	/// Загрузчик
	std::shared_ptr<DrWeb::RemoteRunner::AbstractBootstrap> bootstrap;

	/// Background?
	bool background_mode(false);

	/// Mode
	BootstrapMode bootstrap_mode(BootstrapMode::Daemon);

	/// Разбираемся с аргументами
	std::string name;
	std::string value;
	std::size_t value_offset = std::string::npos;
	for(int i=1; i<argc; ++i) {
		std::string argument(argv[i]);
		
		value_offset = argument.find("=");
		name.clear();
		value.clear();
		
		if (argument.find("--") == 0) {
			name = argument.substr(2, value_offset - 2);
			if (value_offset != std::string::npos) {
				value = argument.substr(value_offset + 1, std::string::npos);
			}
		} else if (argument.find("-") == 0) {
			name = argument.substr(1, value_offset - 1);
			if (value_offset != std::string::npos) {
				value = argument.substr(value_offset + 1, std::string::npos);
			}
		} else {
			/// @note Хз что, а не аргумент
			continue;
		}
		
		if (name.compare("daemon") == 0 || name.compare("d") == 0) {
			bootstrap_mode = BootstrapMode::Daemon;
			continue;
		}

		if (name.compare("test") == 0 || name.compare("t") == 0) {
			bootstrap_mode = BootstrapMode::Test;
			continue;
		}
		
		if (name.compare("version") == 0 || name.compare("v") == 0) {
			bootstrap_mode = BootstrapMode::Version;
			continue;
		}
		
		if (name.compare("help") == 0 || name.compare("h") == 0) {
			bootstrap_mode = BootstrapMode::Help;
			break;
		}

		if (name.compare("config") == 0 || name.compare("c") == 0) {
			configuration_stream.open((value[0] != '~' ? value : (std::getenv("HOME") + value.substr(1))));
			continue;
		}

		if (name.compare("background") == 0 || name.compare("b") == 0) {
			background_mode = true;
			continue;
		}
	}

	/// @note Демонизируемся
	if (background_mode) {
		pid_t pid = fork();

		if (pid < 0) {
			std::cerr << argv[0] << ": Couldn't switch to background: " << strerror(errno) << std::endl;

			exit(EXIT_FAILURE);
		} else if (0 == pid) {
			/// @note Новый сенас
			if (setsid() < 0) {
				exit(EXIT_FAILURE);
			}

			signal(SIGHUP, SIG_IGN);

			pid = fork();
			if (pid < 0) {
				exit(EXIT_FAILURE);
			} else if (pid > 0) {
				_exit(EXIT_SUCCESS);
			}

			chdir("/tmp");

			/// @note Больше нет
			close(STDOUT_FILENO);
			close(STDIN_FILENO);
			close(STDERR_FILENO);
		} else {
			std::cerr << argv[0] << ": Switch to background" << std::endl;

			/// @note родительский процесс завершаем
			_exit(EXIT_SUCCESS);
		}
	}

	openlog(argv[0], LOG_PID, LOG_DAEMON);
	
	/// @note Определяем загрузчик
	switch (bootstrap_mode) {
		case BootstrapMode::Daemon:
			bootstrap.reset(new DrWeb::RemoteRunner::DaemonBootstrap(argv[0], configuration_stream));
			break;
/*
		case BootstrapMode::Test:
			bootstrap.reset(new DrWeb::RemoteRunner::TestBootstrap(argv[0], configuration_stream));
			break;

		case BootstrapMode::Version:
			bootstrap.reset(new DrWeb::RemoteRunner::VersionBootstrap(argv[0], configuration_stream));
			break;

		case BootstrapMode::Test
			bootstrap.reset(new DrWeb::RemoteRunner::HelpBootstrap(argv[0], configuration_stream));
			break;
*/
		default:
			syslog(LOG_ALERT, "Unsupported bootstrap mode = %c", static_cast<char>(bootstrap_mode));
			
			return EXIT_FAILURE;
	}

	/// @note Запускаем
	try {
		int retcode = bootstrap->run();
		closelog();
		
		return retcode ? EXIT_SUCCESS : EXIT_FAILURE;
	} catch (std::exception const &e) {
		syslog(LOG_CRIT, "Stopped abnormally with unexpected exception: %s", e.what());
		closelog();
		
		return EXIT_FAILURE;
	}
}
