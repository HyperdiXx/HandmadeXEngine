#pragma once


#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>

#include "mathexport.h"
#include "types.h"
#include "utils.h"

namespace Math
{
    struct MATH_API vec2f
    {
        union
        {
            struct
            {
                real32 x, y;
            };
            real32 data[2];
        };


        vec2f() : x(0.0f), y(0.0f) {};

        vec2f(const real32 &a, const real32 &b) : x(a), y(b) {};

        inline real32 length() const;
        inline real32 lengthSqr() const;

        inline bool equals(const vec2f &b, real32 tolerance);
        inline void normalize();

        inline bool isZero() const;

        inline void set(const real32 a, const real32 b);
        inline void set(const vec2f& b);

        inline real32 getMin() const;
        inline real32 getMax() const;

        //operators
        inline vec2f operator+(const vec2f & b);
        inline vec2f operator+(const real32& val);

        inline vec2f operator-(const vec2f &b);
        inline vec2f operator-(const real32& val);

        inline vec2f operator*(const real32 &val);
        inline vec2f operator*(const vec2f& b);

        inline vec2f& operator+=(const vec2f& a);
        inline vec2f& operator-=(const vec2f& a);

        inline vec2f& operator*=(const vec2f& a);
        inline vec2f& operator/=(const vec2f& a);

        inline vec2f operator-() const;

        inline bool operator<(const vec2f& other) const;
        inline bool operator<=(const vec2f& other) const;

        inline bool operator>(const vec2f& other) const;
        inline bool operator>=(const vec2f& other) const;

        inline bool operator==(const vec2f& a);
        inline bool operator!=(const vec2f& a);

        friend std::ostream& operator<<(std::ostream& os, const vec2f& v)
        {
            os << "(" << v.x << "," << v.y << ")";
            return os;
        }

    public:

        inline static real32 dotProduct(const vec2f &a, const vec2f &b);
        inline static real32 crossProduct(const vec2f &a, const vec2f &b);
        inline static real32 distance(const vec2f &a, const vec2f &b);
        inline static real32 distanceSqr(const vec2f &a, const vec2f &b);
        inline static vec2f max(const vec2f &a, const vec2f &b);
        inline static vec2f min(const vec2f &a, const vec2f &b);
    };
}
#endif // !VEC2F_H

