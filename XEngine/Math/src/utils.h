#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
#define PI 3.14159265f

    class Utils
    {
    public:

        inline static float toRadians(float degree)
        {
            return degree * (PI / 180.0f);
        }

        inline static float toDegrees(float radians)
        {
            return radians * (180.0f / PI);
        }

        inline static float sin(float radians)
        {
            return sinf(radians);
        }

        inline static float cos(float radians)
        {
            return cosf(radians);
        }

    };

}

