
#pragma once

#ifdef _WIN32

//Win32
#define WIN32_LEAN_AND_MEAN

#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <types.h>
#include <memory>

#endif 

namespace xe_platform
{
#ifdef _WIN32
    typedef HWND window_handle;

    inline HWND& get_window_handle()
    {
        static window_handle window;
        return window;
    }

    bool32 load_library(const char *name);

#endif
}


