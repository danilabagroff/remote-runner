/**
 @file DaemonBootstrap.cpp
 @date 02.07.15

 @author Daniil A Megrabyan
*/

#include "DaemonBootstrap.hpp"

#include "../Core/System/Log.hpp"
#include "../Core/Net/Log.hpp"

#include "../Core/Net/Server/TelnetServer.hpp"
#include "../Core/Net/Socket/ServerSocket.hpp"
#include "../Core/Net/Socket/InetSocketAddress.hpp"
#include "../Core/Net/Socket/UnixSocketAddress.hpp"

#include "../Core/System/Preference/Preference.hpp"

#include "../Core/Launcher.hpp"

#include "../Wand/MakeUnique.hpp"
#include "../Wand/WorkerThread.hpp"
#include "../Wand/AsyncThen.hpp"

namespace DrWeb { namespace RemoteRunner {
	DaemonBootstrap::DaemonBootstrap(const std::string name, std::fstream& configuration_stream)
	:
		AbstractBootstrap(name, configuration_stream)
	{
		/// @note Запускаем отдельный поток и задаем его каждому регистратору
		std::shared_ptr<wand::worker_thread> worker(wand::worker_thread::instance());
		Core::LogRegister<Core::System::Log>::Registrar(worker);
		Core::LogRegister<Core::Net::Log>::Registrar(worker);
		
		Core::LogRegister<Core::System::Log>::Instance().addStream(_systemlog_stream);
		Core::LogRegister<Core::Net::Log>::Instance().addStream(_netlog_stream);
	}
	
	DaemonBootstrap::~DaemonBootstrap()
	{
		/// @note завершаем рабочий поток с журналированием
		std::shared_ptr<wand::worker_thread> dummy(wand::dummy_thread::instance());
		Core::LogRegister<Core::System::Log>::Registrar(dummy);
		Core::LogRegister<Core::Net::Log>::Registrar(dummy);
		
		Core::LogRegister<Core::System::Log>::Instance().removeStream(std::cout);
		Core::LogRegister<Core::Net::Log>::Instance().removeStream(std::cout);
		
		Core::LogRegister<Core::System::Log>::Instance().removeStream(_systemlog_stream);
		Core::LogRegister<Core::Net::Log>::Instance().removeStream(_netlog_stream);
	}
	
	bool DaemonBootstrap::run()
	{
		if (!AbstractBootstrap::boot(true)) {
			return false;
		}
		
		Core::System::Preference preference;

		if (!_configuration.load(preference)) {
			syslog(LOG_ERR, "Unexpected configuration fault");
			
			return false;
		}
		
		/// @xxx А почему мы считаем, что пути файлов всегда заданы?
		_systemlog_stream.open(preference.getSystemLogFile().getPath(), std::ofstream::out | std::ofstream::ate);
		_netlog_stream.open(preference.getNetLogFile().getPath(), std::ofstream::out | std::ofstream::ate);
		
		/// @note Уровни журналирования
		Core::LogRegister<Core::System::Log>::Instance().setLevel(preference.getSystemLogLevel().getLevel());
		Core::LogRegister<Core::Net::Log>::Instance().setLevel(preference.getNetLogLevel().getLevel());
		
		/// @note Врубаем ввод журналов в терминал
		if (preference.getSystemLogOutput().isOn()) {
			Core::LogRegister<Core::System::Log>::Instance().addStream(std::cout);
		}
		
		if (preference.getNetLogOutput().isOn()) {
			Core::LogRegister<Core::Net::Log>::Instance().addStream(std::cout);
		}

		/// Пусковая установка
		Core::Launcher launcher(preference.getApplicationListFile().getPath(), preference.getApplicationTimeout().getTimeout());
		
		/// @note Инициализируем telnet-сервер
		std::shared_ptr<Core::Net::TelnetServer> telnet_server(nullptr);
		switch (preference.getTelnetServerSocketAddress().getFamily()) {
			case Core::System::SocketAddressOption::SocketFamily::TCP:
				telnet_server.reset(new Core::Net::TelnetServer(wand::make_unique<Core::Net::ServerSocket>(wand::make_unique<Core::Net::InetSocketAddress>(preference.getTelnetServerSocketAddress().getHost(), preference.getTelnetServerSocketAddress().getPort())), launcher));
				break;
			case Core::System::SocketAddressOption::SocketFamily::Unix:
				telnet_server.reset(new Core::Net::TelnetServer(wand::make_unique<Core::Net::ServerSocket>(wand::make_unique<Core::Net::UnixSocketAddress>("/" + preference.getTelnetServerSocketAddress().getPath())), launcher));
				break;
			default:
				syslog(LOG_ERR, "TelnetServer cannot be initialized with specified option");

				return false;
				break;
		}
		
		/// @note Поехали!(c)
		return telnet_server->run();
	}
} }
