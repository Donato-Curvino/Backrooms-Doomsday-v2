#ifndef __CROSS_PLATFORM_H
#define __CROSS_PLATFORM_H

#ifdef __SWITCH__
    #define PATH_PREFIX(str) std::string("romfs:/") + str
#else
    #define PATH_PREFIX(str) str
#endif

#endif