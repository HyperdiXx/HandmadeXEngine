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
        vec3(float& a, float& b, float& c) : x(a), y(b), z(c) {};
       
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

        inline vec3 operator*(const float a) const
        {
            return vec3(x * a, y * a, z * a);
        }

        inline vec3 operator/(const float a) const
        {
            return vec3(x / a, y / a, z / a);
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

        vec3 normalize() const
        {
            float length = magnitude();
            return vec3(x / length, y / length, z / length);
        }

        void normalize() noexcept
        {
            float length = magnitude();
            x /= length;
            y /= length; 
            z /= length;
        }

        static float dot(const vec3&a,  const vec3& b) 
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        static vec3 cross(const vec3& a, const vec3& b)
        {
            return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }

        float magnitude() const
        {
            float sqrval = sqrmagnitude();
            return sqrtf(sqrval);
        }

        float sqrmagnitude() const
        {
            return x * x + y * y + z * z;
        }

        static float distance(const vec3& s, const vec3& e)
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

        static vec3 lerp(const vec3& start, const vec3& end, float t)
        {
            return start * (1.0f - t) + end * t;
        }

        static vec3 slerp(const vec3& start, const vec3& end, float dt)
        {

        }

        static vec3 project(const vec3& vect, const vec3& normal)
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
