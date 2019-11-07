#pragma once

#ifndef UTILS_H
#define UTILS_H


#define _USE_MATH_DEFINES

#include "genericmath.h"

#define PI 					(3.1415926535897932f)	
#define SMALL_NUMBER		(1.e-8f)
#define DELTA			    (0.00001f)

struct Utils
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

    inline static void swap(real32 &a, real32 &b)
    {
        real32 tmp = a;
        a = b;
        b = tmp;
    }

    template< typename T >
    inline static T maxVal(const T a, const T b)
    {
        return (a >= b) ? a : b;
    }

    template< typename T >
    inline static T minVal(const T a, const T b)
    {
        return (a <= b) ? a : b;
    }

    template< typename T >
    inline static T abs(T a)
    {
        return a >= 0 ? a : a *= -1;
    }
};

#endif // !UTILS_H

