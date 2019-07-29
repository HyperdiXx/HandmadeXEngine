#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
#define PI 3.14159265f

    inline float toRadians(float degree)
    {
        return degree * (PI / 180.0f);
    }

    inline float toDegrees(float radians)
    {
        return radians * (180.0f / PI);
    }
}

