
#pragma once

#ifdef _WIN32
    #define PLATFORM_WINDOWS
#else
    #define PLATFORM_LINUX
#endif

#ifdef PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN

#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <types.h>
#include <memory>

#endif 

#ifdef PLATFORM_LINUX

#endif


namespace xe_platform
{
#ifdef PLATFORM_WINDOWS
    typedef HWND window_handle;

    inline HWND& get_window_handle()
    {
        static window_handle window;
        return window;
    }

    bool32 load_library(const char *name);

#endif

#ifdef PLATFORM_LINUX

#endif
}


