#pragma once

#ifndef VEC2I_H
#define VEC2I_H

#include <iostream>

#include "types.h"
#include "utils.h"

namespace Math
{
    struct vec2i
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
}
#endif // !vec2i_H

