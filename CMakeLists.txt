cmake_minimum_required(VERSION 2.8)

project(drweb-remoterunner-daemon)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

# Define build type
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# Check c++11
check_cxx_compiler_flag("-std=c++11" CXX_SUPPORTS_CXX11)
if (CXX_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	message(FATAL_ERROR "Requires C++11 support but the '-std=c++11' flag isn't supported.")
endif()

# Set compiler's options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	message("-- Using clang...")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message("-- Using g++...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	message(FATAL_ERROR "-- Unsupported(Intel) compiler.")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	message(FATAL_ERROR "-- Unsupported(MSVC) compiler.")
else()
	message(FATAL_ERROR "-- Unsupported(Unknown) compiler.")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

	# Install configuration files
	install(FILES remote-runnerd.conf DESTINATION /etc COMPONENT remote-runnerd)
	install(FILES remote-runnerd.app.list DESTINATION /etc COMPONENT remote-runnerd)

	set(SOURCE_CORE_NET_SERVER
			remote-runnerd/Core/Net/Server/LinuxServer.cpp
	)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
	# Install configuration files
	install(FILES remote-runnerd.conf DESTINATION /etc COMPONENT remote-runnerd)
	install(FILES remote-runnerd.app.list DESTINATION /etc COMPONENT remote-runnerd)

	set(SOURCE_CORE_NET_SERVER
			remote-runnerd/Core/Net/Server/BSDServer.cpp
	)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	# Default configuration files
	# Not implemented yet
	set(SOURCE_CORE_NET_SERVER
			remote-runnerd/Core/Net/Server/BSDServer.cpp
	)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Default configuration files
	# Not implemented yet
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(SOURCE
		remote-runnerd/AbstractBootstrap.cpp
		remote-runnerd/Build.cpp
		remote-runnerd/Configuration.cpp
		remote-runnerd/Runner.cpp
)

set(SOURCE_WAND
		remote-runnerd/Wand/WorkerThread.cpp
)

set(SOURCE_BOOTSTRAP
		remote-runnerd/Bootstrap/DaemonBootstrap.cpp
)

set(SOURCE_CORE
		remote-runnerd/Core/Net/Buffer/CensoredBuffer.cpp
		remote-runnerd/Core/Net/Buffer/FlexibleBuffer.cpp
		remote-runnerd/Core/Net/Buffer/LimitedBuffer.cpp

		remote-runnerd/Core/Net/Proxy/TelnetProxy.cpp

		remote-runnerd/Core/Net/Request/PayloadAdapter/LaunchRequestCommandAdapter.cpp

		remote-runnerd/Core/Net/Request/LaunchRequest.cpp

		remote-runnerd/Core/Net/Response/TelnetApplicationTimeoutResponse.cpp
		remote-runnerd/Core/Net/Response/TelnetConnectionTimeoutResponse.cpp
		remote-runnerd/Core/Net/Response/TelnetLaunchResponse.cpp

		remote-runnerd/Core/Net/Server/TelnetServer.cpp

		remote-runnerd/Core/Net/Socket/Event/SocketDown.cpp
		remote-runnerd/Core/Net/Socket/Event/SocketError.cpp
		remote-runnerd/Core/Net/Socket/Event/SocketRead.cpp
		remote-runnerd/Core/Net/Socket/Event/SocketUp.cpp
		remote-runnerd/Core/Net/Socket/Event/SocketWrite.cpp

		remote-runnerd/Core/Net/Socket/ClientSocket.cpp
		remote-runnerd/Core/Net/Socket/InetSocketAddress.cpp
		remote-runnerd/Core/Net/Socket/ServerSocket.cpp
		remote-runnerd/Core/Net/Socket/SocketEvent.cpp
		remote-runnerd/Core/Net/Socket/UnixSocketAddress.cpp

		remote-runnerd/Core/Net/AbstractBuffer.cpp
		remote-runnerd/Core/Net/AbstractClient.cpp
		remote-runnerd/Core/Net/AbstractEvent.cpp
		remote-runnerd/Core/Net/AbstractOperation.cpp
		remote-runnerd/Core/Net/AbstractPayload.cpp
		remote-runnerd/Core/Net/AbstractPayloadAdapter.cpp
		remote-runnerd/Core/Net/AbstractProxy.cpp
		remote-runnerd/Core/Net/AbstractRequest.cpp
		remote-runnerd/Core/Net/AbstractResponse.cpp
		remote-runnerd/Core/Net/AbstractServer.cpp
		remote-runnerd/Core/Net/AbstractSocket.cpp
		remote-runnerd/Core/Net/AbstractSocketAddress.cpp
		remote-runnerd/Core/Net/Connection.cpp
		remote-runnerd/Core/Net/Transmission.cpp

		remote-runnerd/Core/System/Option/DataSourceOption.cpp
		remote-runnerd/Core/System/Option/FilePathOption.cpp
		remote-runnerd/Core/System/Option/LicenseOption.cpp
		remote-runnerd/Core/System/Option/LogLevelOption.cpp
		remote-runnerd/Core/System/Option/ResourceLimitOption.cpp
		remote-runnerd/Core/System/Option/SocketAddressOption.cpp
		remote-runnerd/Core/System/Option/StringOption.cpp
		remote-runnerd/Core/System/Option/SwitchOption.cpp
		remote-runnerd/Core/System/Option/TimeoutOption.cpp
		remote-runnerd/Core/System/Option/URIOption.cpp

		remote-runnerd/Core/System/Preference/Preference.cpp

		remote-runnerd/Core/System/AbstractOption.cpp
		remote-runnerd/Core/System/AbstractPreference.cpp

		remote-runnerd/Core/AbstractEvent.cpp
		remote-runnerd/Core/AbstractException.cpp
		remote-runnerd/Core/AbstractInputStream.cpp
		remote-runnerd/Core/AbstractLog.cpp
		remote-runnerd/Core/AbstractStream.cpp
		remote-runnerd/Core/Launcher.cpp
		remote-runnerd/Core/StreamException.cpp
)

add_executable(remote-runnerd ${SOURCE} ${SOURCE_WAND} ${SOURCE_BOOTSTRAP} ${SOURCE_CORE_NET_SERVER} ${SOURCE_CORE})

install(TARGETS remote-runnerd RUNTIME DESTINATION bin COMPONENT remote-runnerd)