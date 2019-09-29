#pragma once

#ifndef VEC2I_H
#define VEC2I_H

#include <iostream>

#include "mathexport.h"
#include "types.h"

namespace Math
{
    struct MATH_API vec2i
    {
        union
        {
            struct
            {
                int32 x, y;
            };
            int32 data[2];
        };

        vec2i() : x(0), y(0) {};
        vec2i(const int32& a, const int32& b) : x(a), y(b) {};

        inline vec2i operator+(const vec2i &b)
        {
            return vec2i(x + b.x, y + b.y);
        }

        inline vec2i operator+(const int32& b)
        {
            return vec2i(x + b, y + b);
        }

        inline vec2i operator-(const vec2i &b)
        {          
            return vec2i(x - b.x, y - b.y);
        }

        inline vec2i operator-(const vec2i &b)
        {
            return vec2i(x - b.x, y - b.y);
        }

        inline vec2i operator*(const int32 &val)
        {
            return vec2i(x * val, y * val);
        }

        inline vec2i operator*(const vec2i &b)
        {
            return vec2i(x * b.x, y * b.y);
        }

        inline vec2i operator/(const vec2i &b)
        {
            return vec2i(x / b.x, y / b.y);
        }

        inline vec2i operator/(const int32 & val)
        {
            return vec2i(x / val, y / val);
        }

        bool operator==(const vec2i& a)
        {
            return x == a.x && y == a.y;
        }

        bool operator!=(const vec2i& a)
        {
            return !(*this == a);
        }

        vec2i& operator+=(const vec2i& a)
        {
            x += a.x;
            y += a.y;
            return *this;
        }

        vec2i& operator-=(const vec2i& a)
        {
            x -= a.x;
            y -= a.y;
            return *this;
        }

        vec2i& operator*=(const vec2i& a)
        {
            x *= a.x;
            y *= a.y;
            return *this;
        }

        vec2i& operator/=(const vec2i& a)
        {
            x /= a.x;
            y /= a.y;
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& os, const vec2i& v)
        {
            os << "(" <<v.x << "," << v.y << ")";
            return os;
        }

    };

}
#endif // !vec2i_H

