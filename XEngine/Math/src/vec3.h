#pragma once

#ifndef VEC3_H
#define VEC3_H

#include "mathexport.h"
#include "types.h"

#include <stdio.h>
#include <stdint.h>
#include <iostream>


namespace Math
{
    struct MATH_API vec3
    {
        static const vec3 ZERO;
        static const vec3 ONE;
        static const vec3 UP;
        static const vec3 RIGHT;
        static const vec3 FORWARD;
        static const vec3 DOWN;
        static const vec3 LEFT;
        static const vec3 BACK;

        union
        {
            struct
            {
                real32 x, y, z;
            };
            real32 data[3];
        };

        vec3() : x(0), y(0), z(0) {};
        vec3(const real32& a, const real32& b, const real32& c) : x(a), y(b), z(c) {};
        vec3(real32& a, real32& b, real32& c) : x(a), y(b), z(c) {};
       
        vec3(const vec3& in) : x{ in.x }, y{ in.y }, z{ in.z } {}
        vec3(vec3&& in) noexcept : x{ in.x }, y{ in.y }, z{ in.z } {}

        inline vec3 operator+(const vec3 &b) const
        {
            return vec3(x + b.x, y + b.y, z + b.z);
        }

        inline vec3 operator-(const vec3 &b) const
        {
            return vec3(x - b.x, y - b.y, z - b.z);
        }

        inline vec3 operator*(const vec3 &b) const
        {
            return vec3(x * b.x, y * b.y, z * b.z);
        }

        inline vec3 operator/(const vec3 &b) const
        {
            return vec3(x / b.x, y / b.y, z / b.z);
        }

        inline vec3 operator*(const real32 a) const
        {
            return vec3(x * a, y * a, z * a);
        }

        inline vec3 operator/(const real32 a) const
        {
            return vec3(x / a, y / a, z / a);
        }

        inline vec3& operator=(const vec3& inVector) 
        {
            x = inVector.x;
            y = inVector.y;
            z = inVector.z;

            return *this;
        }

        inline vec3& operator=(vec3&& inVector) noexcept 
        {
            x = inVector.x;
            y = inVector.y;
            z = inVector.z;

            return *this;
        }

        bool operator==(const vec3& a)
        {
            return x == a.x && y == a.y && z == a.z;
        }

        bool operator!=(const vec3& a)
        {
            return !(*this == a);
        }


        vec3& operator+=(const vec3& a)
        {
            x += a.x;
            y += a.y;
            z += a.z;
            return *this;
        }

        vec3& operator-=(const vec3& a)
        {
            x -= a.x;
            y -= a.y;
            z -= a.z;
            return *this;
        }

        vec3& operator*=(const vec3& a)
        {
            x *= a.x;
            y *= a.y;
            z *= a.z;
            return *this;
        }

        vec3& operator/=(const vec3& a)
        {
            x /= a.x;
            y /= a.y;
            z /= a.z;
            return *this;
        }

        void set(real32 a, real32 b, real32 c)
        {
            x = a;
            y = b;
            z = c;
        }

        vec3 normalize() const
        {
            real32 length = magnitude();
            return vec3(x / length, y / length, z / length);
        }

        void normalize() noexcept
        {
            real32 length = magnitude();
            x /= length;
            y /= length; 
            z /= length;
        }

        static real32 dot(const vec3&a,  const vec3& b) 
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        static vec3 cross(const vec3& a, const vec3& b)
        {
            return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }

        real32 magnitude() const
        {
            real32 sqrval = sqrmagnitude();
            return sqrtf(sqrval);
        }

        real32 sqrmagnitude() const
        {
            return x * x + y * y + z * z;
        }

        static real32 distance(const vec3& s, const vec3& e)
        {
            return (s - e).magnitude();
        }

        static vec3 reflect(const vec3& vect, const vec3& normal)
        {
            vec3 res = normal.normalize();
            return vect - res * dot(vect, res) * 2.0f;
        }

        static vec3 scale(const vec3& a, const vec3& b)
        {
            return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        static vec3 reverseScale(const vec3& a, const vec3& b)
        {
            return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
        }

        static vec3 lerp(const vec3& start, const vec3& end, real32 t)
        {
            return start * (1.0f - t) + end * t;
        }

        static vec3 slerp(const vec3& start, const vec3& end, real32 dt)
        {
            return vec3();
        }

        static vec3 projection(const vec3& vect, const vec3& normal)
        {
            return normal.normalize() * dot(vect, normal);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3& v)
        {
            os << "(" << v.x << "," << v.y << "," << v.z << ")";
            return os;
        }

    };
};
#endif // !VEC3_H