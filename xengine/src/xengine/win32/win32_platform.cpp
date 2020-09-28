
#ifndef PLATFORM_WIN32
#define PLATFORM_WIN32

#ifdef _MSC_VER
    #pragma once
#endif  

inline void* AllocStack(uint32 size)
{
    return alloca(size);
}

inline void* AllocHeap(uint32 size)
{
    return HeapAlloc(GetProcessHeap(), 0, size);
}

inline void* AllocVirtual(uint32 size)
{
    return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);;
}

inline void FreeHeap(void *ptr)
{
    HeapFree(GetProcessHeap(), 0, ptr);
}

inline void FreeVirtual(void *ptr)
{
    VirtualFree(ptr, 0, MEM_RELEASE);
}

//@MOve to LinuxFile
#if defined( __LINUX__ ) || defined( __OSX__ )
#include <sys/types.h>
#endif


#endif
