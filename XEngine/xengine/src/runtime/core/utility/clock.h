#pragma once

#include <windows.h>

namespace XEngine
{
    class Clock
    {
    public:
        Clock() { startTimer(); }
        ~Clock() {}
        
        void startTimer()
        {
            LARGE_INTEGER frequency;
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&mStart);
            Freq = 1.0f / frequency.QuadPart;
        }

        void reset()
        {
            QueryPerformanceCounter(&mStart);
        }

        float elapsed()
        {
            LARGE_INTEGER cur;
            QueryPerformanceCounter(&cur);
            unsigned __int64 timeElapsed = cur.QuadPart - mStart.QuadPart;
            return (float)(timeElapsed * Freq);
        }

        inline LARGE_INTEGER getWallClock()
        {
            LARGE_INTEGER end;
            QueryPerformanceCounter(&end);
            return (end);
        }


    private:
        LARGE_INTEGER mStart;
        double Freq;
    };
}
