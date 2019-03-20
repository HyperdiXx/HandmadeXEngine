#pragma once

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>


namespace Math
{
    template<typename T>
    struct vec3
    {
        T x, y, z;

        vec3() : x(0), y(0), z(0) {};
        vec3(const T& a, const T& b, const T& c) : x(a), y(b), z(c) {};

        friend vec3 operator+(const vec3& a, const vec3 &b)
        {
            return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        friend vec3 operator-(const vec3& a, const vec3 &b)
        {
            return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        friend vec3 operator*(const vec3& a, const vec3 &b)
        {
            return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        friend vec3 operator/(const vec3 &a, const vec3 &b)
        {
            return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3& v)
        {
            os << "(" << v.x << "," << v.y << "," << v.z << ")";
            return os;
        }

    };
};
