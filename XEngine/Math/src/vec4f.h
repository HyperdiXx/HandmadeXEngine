#pragma once

#ifndef VEC4_H
#define VEC4_H

#include "genericmath.h"

namespace Math
{
    struct MATH_API vec4f
    {
        union
        {
            struct
            {
                real32 x, y, z, w;
            };
            real32 data[4];
        };

        vec4f() : x(0), y(0), z(0), w(0) {}
        vec4f(const real32 a, const real32 b, const real32 c, const real32 d) : x(a), y(b), z(c), w(d) {}
        vec4f(const vec4f& a)
        {
            x = a.x;
            y = a.y;
            z = a.z;
            w = a.w;
        }

        vec4f(vec4f&& a)
        {
            x = a.x;
            y = a.y;
            z = a.z;
            w = a.w;
        }

        inline vec4f operator+(const vec4f& a) const;
        inline vec4f operator-(const vec4f& a) const;

        inline vec4f operator*(const vec4f& a) const;
        inline vec4f operator*(const real32 a) const;
        inline vec4f& operator*=(const real32 scalar);
        inline vec4f& operator*=(const vec4f& a);
        
        inline vec4f operator/(const vec4f &a) const;
        inline vec4f operator/(const real32 a) const;
        inline vec4f& operator/=(const vec4f& a);

        inline bool operator==(const vec4f& a);
        inline bool operator!=(const vec4f& a);     
        inline vec4f& operator+=(const vec4f& a);
        inline vec4f& operator-=(const vec4f& a);

        inline vec4f& operator=(const vec4f& a);
        inline vec4f& operator=(vec4f&& a);

        inline void normalize();
      
        vec4f getNormalized(real32 tolerance = TOLERANCE);

        inline real32 getMagnitude() const;

        inline real32 sqrMagnitude() const;
        
        // @Refactor
        static real32 distance(vec4f& s, vec4f& e);
        static vec4f lerp(const vec4f& start, const vec4f& end, real32 t);
        static real32 dot(const vec4f& a, const vec4f& b);

       
         
    };
};

#endif // !VEC4_H

