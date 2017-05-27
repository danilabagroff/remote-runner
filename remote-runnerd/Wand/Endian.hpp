/**
 @file
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef Wand_Endian_hpp
#define Wand_Endian_hpp

#include <arpa/inet.h>
#include <cstdint>

#if defined(__linux__)
#  include <netinet/in.h>
#  include <endian.h>
#  define ntohll(x) be64toh(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__)
#  include <sys/endian.h>
#  define ntohll(x) be64toh(x)
#elif defined(__OpenBSD__)
#  include <sys/types.h>
#  define ntohll(x) betoh64(x)
#endif

#endif
