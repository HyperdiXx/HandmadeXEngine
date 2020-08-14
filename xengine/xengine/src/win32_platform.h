#pragma once

#ifndef WIN32_PLATFORM_H
#define WIN32_PLATFORM_H

namespace xe_platform
{
    struct win32_window_state
    {
        bool32 is_closed;
    };

    struct timer
    {
        LARGE_INTEGER start;
        real64 frequ;
    };

    struct thread
    {
        uint32 id;
        HANDLE semaphore;
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

    bool32 load_DLL(const char *name);

    void shutdownApp();

    thread createThread();

    void join();
    void detach();

    void notify_one();
    void notify_all();
}
#endif // !WIN32_PLATFORM_H

