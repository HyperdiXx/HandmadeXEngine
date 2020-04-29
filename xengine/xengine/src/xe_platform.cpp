#include "xe_platform.h"

bool32 xe_platform::load_library(const char *name)
{
    HMODULE library = LoadLibrary(name);
    if (library)
        return false;
    return true;
}

void xe_platform::start_timer(timer *time)
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time->start);
    time->frequ = 1.0f / frequency.QuadPart;
}

void xe_platform::reset_timer(timer *time)
{
    QueryPerformanceCounter(&time->start);
}

real32 xe_platform::time_elapsed(timer *time)
{
    LARGE_INTEGER cur;
    QueryPerformanceCounter(&cur);
    unsigned __int64 timeElapsed = cur.QuadPart - time->start.QuadPart;
    return (real32)(timeElapsed * time->frequ);
}

LARGE_INTEGER xe_platform::get_wall_clock()
{
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    return (end);
}
