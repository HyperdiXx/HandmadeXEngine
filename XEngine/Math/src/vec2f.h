#pragma once


#ifndef VEC2F_H
#define VEC2F_H


#include "mathexport.h"
#include "types.h"

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

        inline vec2f operator+(const vec2f & b);       

        inline vec2f operator+(const real32& val);
        
        inline vec2f operator-(const vec2f &b);
        
        inline vec2f operator-(const real32& val);
        
        inline vec2f operator*(const real32 &val);

        inline vec2f operator*(const vec2f& b);

        vec2f& operator+=(const vec2f& a);
        
        vec2f& operator-=(const vec2f& a);

        vec2f& operator*=(const vec2f& a);
        
        vec2f& operator/=(const vec2f& a);
        
        vec2f operator-() const;
        
        bool operator==(const vec2f& a);
        
        bool operator!=(const vec2f& a);

        real32 size() const;
        void normalize() const;

    public:

        inline static real32 dotProduct(const vec2f &a, const vec2f &b);
        inline static real32 crossProduct(const vec2f &a, const vec2f &b);


    };

    // functions 

    inline vec2f vec2f::operator+(const vec2f & b)
    {
        return vec2f(x + b.x, y + b.y);
    }

    inline vec2f vec2f::operator+(const real32& val)
    {
        return vec2f(x + val, y + val);
    }

    inline vec2f vec2f::operator-(const vec2f &b)
    {
        return vec2f(x - b.x, y - b.y);
    }

    inline vec2f vec2f::operator-(const real32& val)
    {
        return vec2f(x - val, y - val);
    }

    inline vec2f vec2f::operator*(const real32 &val)
    {
        return vec2f(x * val, y * val);
    }

    inline vec2f vec2f::operator*(const vec2f& b)
    {
        return vec2f(x * b.x, y * b.y);
    }

    inline vec2f& vec2f::operator+=(const vec2f& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    inline vec2f& vec2f::operator-=(const vec2f& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    inline vec2f& vec2f::operator*=(const vec2f& a)
    {
        x *= a.x;
        y *= a.y;
        return *this;
    }

    inline vec2f& vec2f::operator/=(const vec2f& a)
    {
        x /= a.x;
        y /= a.y;
        return *this;
    }

    inline vec2f vec2f::operator-() const
    {
        return vec2f(-x, -y);
    }

    bool vec2f::operator==(const vec2f& a)
    {
        return x == a.x && y == a.y;
    }

    bool vec2f::operator!=(const vec2f& a)
    {
        return !(*this == a);
    }

    inline void vec2f::normalize() const
    {
        const real32 sqrS = x * x + y * y;
        
        if (sqrS > 0.0000001f)
        {
            return;
        }

        
    }

    inline real32 vec2f::dotProduct(const vec2f & a, const vec2f & b)
    {
        return real32();
    }

    inline real32 vec2f::crossProduct(const vec2f & a, const vec2f & b)
    {
        return real32();
    }


}





#endif // !VEC2F_H

