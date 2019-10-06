#pragma once

#ifndef VEC2I_H
#define VEC2I_H

#include <iostream>

#include "mathexport.h"
#include "types.h"
#include "utils.h"

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

        inline real32 length() const;
        inline int32 lengthSqr() const;
        inline void normalize();
       
        inline vec2i operator+(const vec2i& a);
        inline vec2i operator+(const int32& b);

        inline vec2i operator-(const vec2i& a);
        inline vec2i operator-(const int32& b);

        inline vec2i operator*(const vec2i& a);
        inline vec2i operator*(const int32& b);

        inline vec2i operator/(const vec2i& a);
        inline vec2i operator/(const int32& b);

        inline bool operator==(const vec2i& a);
        inline bool operator!=(const vec2i& a);

        inline vec2i& operator+=(const vec2i& a);
        inline vec2i& operator-=(const vec2i& a);

        inline vec2i& operator*=(const vec2i& a);
        inline vec2i& operator/=(const vec2i& a);

        friend std::ostream& operator<<(std::ostream& os, const vec2i& v)
        {
            os << "(" <<v.x << "," << v.y << ")";
            return os;
        }

    };

    inline real32 vec2i::length() const
    {
        return sqrtf(lengthSqr());
    }

    inline int32 vec2i::lengthSqr() const
    {
        return x * x + y * y;
    }

    inline vec2i vec2i::operator+(const vec2i &b)
    {
        return vec2i(x + b.x, y + b.y);
    }

    inline vec2i vec2i::operator+(const int32& b)
    {
        return vec2i(x + b, y + b);
    }

    inline vec2i vec2i::operator-(const vec2i &b)
    {
        return vec2i(x - b.x, y - b.y);
    }

    inline vec2i vec2i::operator-(const int32& b)
    {
        return vec2i(x - b, y - b);
    }


    inline vec2i vec2i::operator*(const int32 &val)
    {
        return vec2i(x * val, y * val);
    }

    inline vec2i vec2i::operator*(const vec2i &b)
    {
        return vec2i(x * b.x, y * b.y);
    }

    inline vec2i vec2i::operator/(const vec2i &b)
    {
        return vec2i(x / b.x, y / b.y);
    }

    inline vec2i vec2i::operator/(const int32 & val)
    {
        return vec2i(x / val, y / val);
    }

    inline bool vec2i::operator==(const vec2i& a)
    {
        return x == a.x && y == a.y;
    }

    inline bool vec2i::operator!=(const vec2i& a)
    {
        return !(*this == a);
    }

    inline vec2i& vec2i::operator+=(const vec2i& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    inline vec2i& vec2i::operator-=(const vec2i& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    inline vec2i& vec2i::operator*=(const vec2i& a)
    {
        x *= a.x;
        y *= a.y;
        return *this;
    }

    inline vec2i& vec2i::operator/=(const vec2i& a)
    {
        x /= a.x;
        y /= a.y;
        return *this;
    }

}
#endif // !vec2i_H

