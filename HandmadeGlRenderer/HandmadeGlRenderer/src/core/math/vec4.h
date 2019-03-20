#pragma once

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>


namespace Math
{
    template<typename T>
    struct vec4
    {
        T x, y, z, w;

        vec4() : x(0), y(0), z(0), w(0) {};
        vec4(const T& a, const T& b, const T& c, const T& d) : x(a), y(b), z(c), w(d) {};

        friend vec4 operator+(const vec4& a, const vec4 &b)
        {
            return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
        }

        friend vec4 operator-(const vec4& a, const vec4 &b)
        {
            return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w + b.w);
        }

        friend vec4 operator*(const vec4& a, const vec4 &b)
        {
            return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
        }

        friend vec4 operator/(const vec4 &a, const vec4 &b)
        {
            return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec4& v)
        {
            os << "(" << v.x << "," << v.y << ","<< v.z << "," << v.w << ")";
            return os;
        }

    };
};

