
#pragma once

#include "config.h"

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

    #ifdef GAPI_DX11
        #include <DirectXMath.h>
        #include <DirectXPackedVector.h>       
    #endif // 

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

    inline HDC& get_dc()
    {
        static HDC dc = GetDC(get_window_handle());
        return dc;
    }

    bool32 load_library(const char *name);

    struct timer
    {
        LARGE_INTEGER start;
        double frequ;
    };
    
    void start_timer(timer *time);
    void reset_timer(timer *time);   
    real32 time_elapsed(timer *time);
 
    inline LARGE_INTEGER get_wall_clock();
   

#endif

#ifdef PLATFORM_LINUX

#endif
}


