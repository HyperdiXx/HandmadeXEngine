
#pragma once

#include "xe_config.h"

#ifdef _WIN32
    #define PLATFORM_WINDOWS
#else
    #define PLATFORM_LINUX
#endif

#ifdef PLATFORM_WINDOWS
#define XE_DEBUG
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
   
    struct win32_window_state
    {
        bool32 is_closed;
    };

    struct timer
    {
        LARGE_INTEGER start;
        real64 frequ;
    };
   
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

    inline HINSTANCE& get_hInstance()
    {
        static HINSTANCE hi;
        return hi;
    }

    inline win32_window_state& get_window_state()
    {
        static win32_window_state windows;
        return windows;
    }

    WNDCLASS create_platform_win32window();


    void open_console();
    void update_platform();

    bool32 init_win32_platform(uint32 window_w, uint32 window_h);
    void destroy_platform_window();

    void start_timer(timer *time);
    void reset_timer(timer *time);   
    real32 time_elapsed(timer *time);
 
    inline LARGE_INTEGER get_wall_clock();
   
    bool32 load_library(const char *name);

#endif

#ifdef PLATFORM_LINUX

    void create_platform_linuxwindow();

#endif
}


