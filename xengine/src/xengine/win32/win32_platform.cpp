
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
    return VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);;
}

inline void FreeHeap(void *ptr)
{
    HeapFree(GetProcessHeap(), 0, ptr);
}

inline void FreeVirtual(void *ptr)
{
    VirtualFree(ptr, 0, MEM_RELEASE);
}

internal bool32 Win32IsFileExist(const char* path)
{
    return GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES;
}

internal bool32 Win32IsDirectoryExist(const char *path)
{
    DWORD file_attrib = GetFileAttributesA(path);

    return (file_attrib != INVALID_FILE_ATTRIBUTES &&
           (file_attrib & FILE_ATTRIBUTE_DIRECTORY));
}

internal void Win32DeleteFile(const char* path)
{
    DeleteFileA(path);
}

internal bool32 Win32MkDir(const char* path)
{
    return CreateDirectoryA(path, 0);
}

internal bool32 Win32DelDir(const char* path)
{
    return RemoveDirectoryA(path);
}

internal bool32 Win32CopyFile(const char* src, const char* dst)
{
    if (Win32IsFileExist(src) && Win32IsFileExist(dst))
    {
        return CopyFile(src, dst, 0);
    }

    return false;
}


//@MOve to LinuxFile
#if defined( __LINUX__ ) || defined( __OSX__ )
#include <sys/types.h>
#endif


#endif
