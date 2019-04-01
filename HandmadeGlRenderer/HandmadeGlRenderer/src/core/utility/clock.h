#pragma once

#include <windows.h>

namespace XEngine
{
    class Clock
    {
    public:
        Clock()
        {

        }

        void reset()
        {

        }


    private:
        LARGE_INTEGER mStart;
        double Freq;
    };
}
