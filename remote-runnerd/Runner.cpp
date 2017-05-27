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

int main(int argc, char* argv[])
{
	/// Конфигурационный поток
	std::fstream configuration_stream;
	
	/// Загрузчик
	std::shared_ptr<DrWeb::RemoteRunner::AbstractBootstrap> bootstrap;
	
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
			bootstrap.reset(new DrWeb::RemoteRunner::DaemonBootstrap(argv[0], configuration_stream, std::cout, std::cerr));
			continue;
		}
		
		/// @note Используем только один вариант загрузчика :(
/*
		if (name.compare("test") == 0 || name.compare("t") == 0) {
			bootstrap.reset(new DrWeb::RemoteRunner::TestBootstrap(argv[0], configuration_stream, std::cout, std::cerr));
			continue;
		}
		
		if (name.compare("version") == 0 || name.compare("v") == 0) {
			bootstrap.reset(new DrWeb::RemoteRunner::VersionBootstrap(argv[0], configuration_stream, std::cout, std::cerr));
			continue;
		}
		
		if (name.compare("help") == 0 || name.compare("h") == 0) {
			bootstrap.reset(new DrWeb::RemoteRunner::HelpBootstrap(argv[0], configuration_stream, std::cout, std::cerr));
			break;
		}
*/
		if (name.compare("config") == 0 || name.compare("c") == 0) {
			configuration_stream.open((value[0] != '~' ? value : (std::getenv("HOME") + value.substr(1))));
			continue;
		}
	}

	/// @note Определям дефолтный загрузчик, если он не был определен ранее
	if (nullptr == bootstrap) {
		bootstrap.reset(new DrWeb::RemoteRunner::DaemonBootstrap(argv[0], configuration_stream, std::cout, std::cerr));
	}

	/// @note Запускаем
	try {
		return bootstrap->run() ? EXIT_SUCCESS : EXIT_FAILURE;
	} catch (std::exception const &e) {
		std::cerr << argv[0] << ": Stopped abnormally with unexpected exception (" << e.what() << ")" << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
