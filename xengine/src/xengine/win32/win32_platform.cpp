
#ifndef PLATFORM_WIN32
#define PLATFORM_WIN32

#ifdef _MSC_VER
    #pragma once
#endif  

inline void* AllocStack(uint32 size)
{
    return (void*)0;
}

inline void* AllocHeap(uint32 size)
{
    return malloc(size);
}

inline void FreeHeap(void *ptr)
{
    free(ptr);
}

//@MOve to LinuxFile
#if defined( __LINUX__ ) || defined( __OSX__ )
#include <sys/types.h>
#endif


#endif
