#pragma once

#ifndef VEC3F_H
#define VEC3F_H

#include "mathexport.h"
#include "types.h"

#include <stdio.h>
#include <stdint.h>
#include <iostream>


namespace Math
{
    struct MATH_API vec3f
    {
        static const vec3f ZERO;
        static const vec3f ONE;
        static const vec3f UP;
        static const vec3f RIGHT;
        static const vec3f FORWARD;
        static const vec3f DOWN;
        static const vec3f LEFT;
        static const vec3f BACK;

        union
        {
            struct
            {
                real32 x, y, z;
            };
            real32 data[3];
        };

        vec3f() : x(0), y(0), z(0) {};
        vec3f(const real32& a, const real32& b, const real32& c) : x(a), y(b), z(c) {};
        vec3f(real32& a, real32& b, real32& c) : x(a), y(b), z(c) {};
       
        vec3f(const vec3f& in) : x{ in.x }, y{ in.y }, z{ in.z } {}
        vec3f(vec3f&& in) noexcept : x{ in.x }, y{ in.y }, z{ in.z } {}

        inline vec3f operator+(const vec3f &b) const
        {
            return vec3f(x + b.x, y + b.y, z + b.z);
        }

        inline vec3f operator-(const vec3f &b) const
        {
            return vec3f(x - b.x, y - b.y, z - b.z);
        }

        inline vec3f operator*(const vec3f &b) const
        {
            return vec3f(x * b.x, y * b.y, z * b.z);
        }

        inline vec3f operator/(const vec3f &b) const
        {
            return vec3f(x / b.x, y / b.y, z / b.z);
        }

        inline vec3f operator*(const real32 a) const
        {
            return vec3f(x * a, y * a, z * a);
        }

        inline vec3f operator/(const real32 a) const
        {
            return vec3f(x / a, y / a, z / a);
        }

        inline vec3f& operator=(const vec3f& inVector) 
        {
            x = inVector.x;
            y = inVector.y;
            z = inVector.z;

            return *this;
        }

        inline vec3f& operator=(vec3f&& inVector) noexcept 
        {
            x = inVector.x;
            y = inVector.y;
            z = inVector.z;

            return *this;
        }

        bool operator==(const vec3f& a)
        {
            return x == a.x && y == a.y && z == a.z;
        }

        bool operator!=(const vec3f& a)
        {
            return !(*this == a);
        }


        vec3f& operator+=(const vec3f& a)
        {
            x += a.x;
            y += a.y;
            z += a.z;
            return *this;
        }

        vec3f& operator-=(const vec3f& a)
        {
            x -= a.x;
            y -= a.y;
            z -= a.z;
            return *this;
        }

        vec3f& operator*=(const vec3f& a)
        {
            x *= a.x;
            y *= a.y;
            z *= a.z;
            return *this;
        }

        vec3f& operator/=(const vec3f& a)
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

        vec3f getNormalized() const
        {
            real32 length = getMagnitude();
            return vec3f(x / length, y / length, z / length);
        }

        void normalize() noexcept
        {
            real32 length = getMagnitude();
            x /= length;
            y /= length; 
            z /= length;
        }

        static real32 dot(const vec3f&a,  const vec3f& b) 
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        static vec3f cross(const vec3f& a, const vec3f& b)
        {
            return vec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }

        inline real32 getMagnitude() const
        {
            real32 sqrval = sqrmagnitude();
            return sqrtf(sqrval);
        }

        real32 sqrmagnitude() const
        {
            return x * x + y * y + z * z;
        }

        static real32 distance(const vec3f& s, const vec3f& e)
        {
            return (s - e).getMagnitude();
        }

        static vec3f reflect(const vec3f& vect, const vec3f& normal)
        {
            vec3f res = normal.getNormalized();
            return vect - res * dot(vect, res) * 2.0f;
        }

        static vec3f scale(const vec3f& a, const vec3f& b)
        {
            return vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        static vec3f reverseScale(const vec3f& a, const vec3f& b)
        {
            return vec3f(a.x / b.x, a.y / b.y, a.z / b.z);
        }

        static vec3f lerp(const vec3f& start, const vec3f& end, real32 t)
        {
            return start * (1.0f - t) + end * t;
        }

        static vec3f slerp(const vec3f& start, const vec3f& end, real32 dt)
        {
            return vec3f();
        }

        static vec3f projection(const vec3f& vect, const vec3f& normal)
        {
            return normal.getNormalized() * dot(vect, normal);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3f& v)
        {
            os << "(" << v.x << "," << v.y << "," << v.z << ")";
            return os;
        }

    };
};
#endif // !vec3ff_H