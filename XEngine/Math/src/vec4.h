#pragma once

#ifndef VEC4_H
#define VEC4_H

#include <stdio.h>
#include <stdint.h>
#include <iostream>

#include "mathexport.h"

namespace Math
{
    template<typename T>
    struct MATH_API vec4
    {
        union
        {
            struct
            {
                T x, y, z, w;
            };
            T data[4];
        };

        vec4() : x(0), y(0), z(0), w(0) {};
        vec4(const T& a, const T& b, const T& c, const T& d) : x(a), y(b), z(c), w(d) {};

        inline vec4 operator+(const vec4 &b)
        {
            return vec4(x + b.x, y + b.y, z + b.z, w + b.w);
        }

        inline vec4 operator-( const vec4 &b)
        {
            return vec4(x - b.x, y - b.y, z - b.z, w + b.w);
        }

        inline vec4 operator*(const vec4 &b)
        {
            return vec4(x * b.x, y * b.y, z * b.z, w * b.w);
        }

        inline vec4 operator/(const vec4 &b)
        {
            return vec4(x / b.x, y / b.y, z / b.z, w / b.w);
        }


        bool operator==(const vec4& a)
        {
            return x == a.x && y == a.y && z = a.z && w = a.w;
        }

        bool operator!=(const vec4& a)
        {
            return !(*this == a);
        }

        inline vec4& operator*(real32 value) const
        {
            return vec4(x * value, y * value, z * value, w * value);
        }

        vec4& operator+=(const vec4& a)
        {
            x += a.x;
            y += a.y;
            z += a.z;
            w += a.w;
            return *this;
        }

        vec4& operator-=(const vec4& a)
        {
            x -= a.x;
            y -= a.y;
            z -= a.z;
            w -= a.w;
            return *this;
        }

        vec4& operator*=(const vec4& a)
        {
            x *= a.x;
            y *= a.y;
            z *= a.z;
            w *= a.w;
            return *this;
        }

        vec4& operator/=(const vec4& a)
        {
            x /= a.x;
            y /= a.y;
            z /= a.z;
            w /= a.w;
            return *this;
        }

        real32 normalize()
        {
            real32 length = magnitude();
            x /= length;
            y /= length;
            z /= length;
            w /= length;
        }

        real32 magnitude() const 
        {
            return sqrtf(sqrmagnitude());
        }

        real32 sqrmagnitude() const
        {
            x * x + y * y + z * z + w * w;
        }

        static real32 distance(const vec4& s, const vec4& e)
        {
            return (s - e).magnitude();
        }

        static vec4 lerp(const vec4& start, const vec4& end, real32 t)
        {
            return start * (1.0f - t) + end * t;
        }

        static vec4 projection(const vec4& in, const vec4& normalvec)
        {
            return vec4();
        }

        static real32 dot(const vec4& a, const vec4& b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        friend std::ostream& operator<<(std::ostream& os, const vec4& v)
        {
            os << "(" << v.x << "," << v.y << ","<< v.z << "," << v.w << ")";
            return os;
        }

    };
};

#endif // !VEC4_H

