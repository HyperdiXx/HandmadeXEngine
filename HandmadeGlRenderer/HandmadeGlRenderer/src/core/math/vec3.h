#pragma once


#include <stdio.h>
#include <stdint.h>
#include <iostream>


namespace maths
{
    struct vec3
    {

        union
        {
            struct
            {
                float x, y, z;
            };
            float data[3];
        };

        vec3() : x(0), y(0), z(0) {};
        vec3(const float& a, const float& b, const float& c) : x(a), y(b), z(c) {};

        inline vec3 operator+(const vec3 &b)
        {
            return vec3(x + b.x, y + b.y, z + b.z);
        }

        inline vec3 operator-(const vec3 &b)
        {
            return vec3(x - b.x, y - b.y, z - b.z);
        }

        inline vec3 operator*(const vec3 &b)
        {
            return vec3(x * b.x, y * b.y, z * b.z);
        }

        inline vec3 operator/(const vec3 &b)
        {
            return vec3(x / b.x, y / b.y, z / b.z);
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

        inline float dot(const vec3& a) const
        {
            return x * a.x + y * a.y + z * a.z;
        }

        inline vec3 cross(const vec3& a) const
        {
            return vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3& v)
        {
            os << "(" << v.x << "," << v.y << "," << v.z << ")";
            return os;
        }

    };
};
