
#ifndef PLATFORM_WIN32
#define PLATFORM_WIN32

#ifdef _MSC_VER
    #pragma once
#endif  

inline void* Win32AllocStack(uint64 size)
{
    return alloca(size);
}

inline void* Win32AllocHeap(uint64 size)
{
    return HeapAlloc(GetProcessHeap(), 0, size);
}

inline void* Win32AllocVirtual(void *ptr, uint64 size)
{
    return VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
}

inline void* Win32Realocate(void *ptr, uint64 size)
{
    return realloc(ptr, size);
}

inline void Win32FreeHeap(void *ptr)
{
    HeapFree(GetProcessHeap(), 0, ptr);
}

inline void Win32FreeVirtual(void *ptr)
{
    VirtualFree(ptr, 0, MEM_RELEASE);
}

//@MOve to LinuxFile
#if defined( __LINUX__ ) || defined( __OSX__ )
#include <sys/types.h>
#endif


#endif
