//
//  Server.hpp
//
//  Created by Daniil A Megrabyan on 25.03.15.
//  Copyright (c) 2015 Cadabra Systems. All rights reserved.
//

#ifndef DrWeb_RemoteRunner_Server_Server_hpp
#define DrWeb_RemoteRunner_Server_Server_hpp

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
//define something for Windows (64-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Mac OS X
#include "BSDServer.hpp"
#else
// Unsupported platform
#endif
#elif __linux
#include "LinuxServer.hpp"
#elif BSD
#include "BSDServer.hpp"
#elif __sun
#include "SolarisServer.hpp"
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#endif
