#pragma once

#include <stdio.h>
#include <stdint.h>
#include <iostream>


namespace maths
{
    template<typename T>
    struct vec4
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

        friend std::ostream& operator<<(std::ostream& os, const vec4& v)
        {
            os << "(" << v.x << "," << v.y << ","<< v.z << "," << v.w << ")";
            return os;
        }

    };
};

