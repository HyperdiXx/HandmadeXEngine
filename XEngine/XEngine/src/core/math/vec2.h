#pragma once

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>

namespace Math
{
    template<typename T>
    struct vec2
    {
        union
        {
            struct
            {
                T x, y;
            };
            T data[2];
        };

        vec2() : x(0), y(0) {};
        vec2(const T& a, const T& b) : x(a), y(b) {};

        inline vec2 operator+(const vec2 &b)
        {
            return vec2(x + b.x, y + b.y);
        }

        inline vec2 operator-(const vec2 &b)
        {          
            return vec2(x - b.x, y - b.y);
        }

        inline vec2 operator*(const vec2 &b)
        {
            return vec2(x * b.x, y * b.y);
        }

        inline vec2 operator/(const vec2 &b)
        {
            return vec2(x / b.x, y / b.y);
        }

        bool operator==(const vec2& a)
        {
            return x == a.x && y == a.y;
        }

        bool operator!=(const vec2& a)
        {
            return !(*this == a);
        }

        vec2& operator+=(const vec2& a)
        {
            x += a.x;
            y += a.y;
            return *this;
        }

        vec2& operator-=(const vec2& a)
        {
            x -= a.x;
            y -= a.y;
            return *this;
        }

        vec2& operator*=(const vec2& a)
        {
            x *= a.x;
            y *= a.y;
            return *this;
        }

        vec2& operator/=(const vec2& a)
        {
            x /= a.x;
            y /= a.y;
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& os, const vec2& v)
        {
            os << "(" <<v.x << "," << v.y << ")";
            return os;
        }

    };

}
