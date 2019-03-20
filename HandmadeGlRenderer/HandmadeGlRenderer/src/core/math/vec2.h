#pragma once

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>

namespace Math
{
    template<typename T>
    struct vec2
    {
        T x, y;

        vec2() : x(0), y(0) {};
        vec2(const T& a, const T& b) : x(a), y(b) {};

        friend vec2 operator+(const vec2& a, const vec2 &b)
        {
            return vec2(a.x + b.x, a.y + b.y);
        }

        friend vec2 operator-(const vec2& a, const vec2 &b)
        {          
            return vec2(a.x - b.x, a.y - b.y);
        }

        friend vec2 operator*(const vec2& a, const vec2 &b)
        {
            return vec2(a.x * b.x, a.y * b.y);
        }

        friend vec2 operator/(const vec2 &a, const vec2 &b)
        {
            return vec2(a.x / b.x, a.y / b.y);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec2& v)
        {
            os << "(" <<v.x << "," << v.y << ")";
            return os;
        }

    };

}
