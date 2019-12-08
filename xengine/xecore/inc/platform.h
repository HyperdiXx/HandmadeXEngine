#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
	#ifdef _WIN64
		#define WINDOWS64
	#else
		#define WINDOWS32
	#endif
#elif defined(__linux__)
	#ifdef __x86_64__
		#define LINUX64
	#else
		#define LINUX32
	#endif
#else
	#error Platform not supported
#endif

#ifdef WINDOWS64
    #include <stdint.h>
#endif   

#ifdef LINUX64
    #include <sys/types.h>
#endif // LINUX64

#endif // !PLATFORM_H

