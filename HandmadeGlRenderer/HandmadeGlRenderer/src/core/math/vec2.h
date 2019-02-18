#pragma once

#include <math.h>
#include <stdio.h>
#include <stdint.h>


namespace Math
{
    template<typename T>
    struct vec2
    {
        union
        {
            struct
            {
                T x, y;
            };
            T v[2];
        };

        vec2() : x(0), y(0) {};
        vec2();
        vec2();

        friend vec2 operator+(const vec2 &a, const vec2 &b)
        {
            return vec2(a.x + b.x, a.y + b.y);
        }

        friend vec2 operator-(const vec2 &a, const vec2 &b)
        {
            return vec2(a.x - b.x, a.y - b.y);
        }

        friend vec2 operator*(const vec2 &a, const vec2 &b)
        {
            return vec2(a.x * b.x, a.y * b.y);
        }

        friend vec2 operator*(const vec2 &a, const T &b)
        {
            return vec2(a.x * b, a.y * b);
        }


    };

}
