#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace maths
{
    inline float toRadians(float degree)
    {
        return degree * (M_PI / 180.0f);
    }

}

