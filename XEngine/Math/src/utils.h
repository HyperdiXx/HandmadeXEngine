#pragma once

#define _USE_MATH_DEFINES

#include "types.h"

namespace Math
{
#define PI 3.14159265f

    class Utils
    {
    public:

        inline static real32 toRadians(real32 degree)
        {
            return degree * (PI / 180.0f);
        }

        inline static real32 toDegrees(real32 radians)
        {
            return radians * (180.0f / PI);
        }

        inline static real32 sin(real32 radians)
        {
            return sinf(radians);
        }

        inline static real32 cos(real32 radians)
        {
            return cosf(radians);
        }

        inline void swap(real32 &a, real32 &b)
        {
            real32 tmp = a;
            a = b;
            b = tmp;
        }

    };

}

