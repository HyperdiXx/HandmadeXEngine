#pragma once

#ifndef QUATERNION_H
#define QUATERNION_H

#include "mat4.h"
#include "utils.h"

namespace Math
{
    /**
      * Quaternion represents 3d rotations
      *
      *
      */
    struct MATH_API Quaternion
    {
        static const Quaternion identity;

        union
        {
            struct
            {
                real32 x, y, z, w;               
            };
            real32 data[4];
        };

        Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
        Quaternion(real32 xV, real32 yV, real32 zV, real32 wV) : x(xV), y(yV), z(zV), w(wV) {}
        Quaternion(const Quaternion& b) : x(b.x), y(b.y), z(b.z), w(b.w) {}
        Quaternion(Quaternion&& b) noexcept : x(b.x), y(b.y), z(b.z), w(b.w) {}
        Quaternion(vec3f& val, real32 angle) {}
    
        Quaternion(real32 xAngle, real32 yAngle, real32 zAngle)
        {
            // Convert to radians from degrees
            xAngle = Utils::toRadians(xAngle);
            yAngle = Utils::toRadians(yAngle);
            zAngle = Utils::toRadians(zAngle);

            Quaternion roll(MathGeneral::Sin(xAngle * 0.5f), 0, 0, MathGeneral::Cos(xAngle * 0.5f));
            Quaternion pitch(0, MathGeneral::Sin(yAngle * 0.5f), 0, MathGeneral::Cos(yAngle * 0.5f));
            Quaternion yaw(0, 0, MathGeneral::Sin(zAngle * 0.5f), MathGeneral::Cos(zAngle * 0.5f));

            // Order: z * y * x
            *this = (yaw * pitch * roll).getNormalized();

        }

        //inline mat4 getMatrix() const;
        //inline void getMatrix(mat4* mat) const;
        //inline vec3f getEulerAngle() const;

        inline void invert();
        inline void normalize(real32 tolerance = TOLERANCE);

        inline real32 length() const;
        inline real32 lengthSqr() const;

        inline bool isNormalized() const;

        inline Quaternion getInverted();
        inline Quaternion getNormalized() const;

        //inline static Quaternion rotate(const vec3f& euler);
        //inline static Quaternion rotate(const mat4& matrix);
        //inline static Quaternion rotate(const vec3f& src, const vec3f& dest, const vec3f& r = vec3f(0.0f, 0.0f, 0.0f));
        //inline static Quaternion rotate(const vec3f& vec, real32 angle);
        
        //inline static Quaternion rotateFast(const vec3f& euler);
        //inline static Quaternion rotateFast(const mat4& matrix);
        //inline static Quaternion rotateFast(const vec3f& vec, real32 angle);
        //inline static Quaternion rotateFast(const vec3f& src, const vec3f& dest, const vec3f& r = vec3f(0.0f, 0.0f, 0.0f));

        //Convertion
        //inline void convertToAxisAngle(vec3f& vec, real32& angle) const;
       
        inline static real32 dot(const Quaternion& a, const Quaternion& b);
        inline static Quaternion nlerp(const Quaternion& q1, const Quaternion& q2, real32 t);
        //inline Quaternion slerp(const Quaternion& q1, const Quaternion& q2, real32 t);
        
        //inline vec3f addToVec(const vec3f& vec) const;

        //inline void constructFromEulerAngles(const vec3f& euler);
        //inline void constructFromVecAngle(const vec3f& vec, real32 angle);
        //inline void constructFromMatrix(const mat4& matrix);
        //inline void constructFromVecs(const vec3f& source, const vec3f& dest, const vec3f& r = vec3f(0.0f, 0.0f, 0.0f));

        /**
        * Operators 
        */
        inline Quaternion& operator=(Quaternion&& b) noexcept;
        inline Quaternion& operator*=(const Quaternion& quat);
        inline Quaternion operator*(const Quaternion& q) const;
        inline Quaternion operator*(const real32 s) const;
        inline Quaternion operator/(const Quaternion& q) const;
        inline Quaternion& operator/=(const Quaternion& q);

        inline bool operator==(Quaternion& b) const;
        inline bool operator!=(const Quaternion& b) const;
        inline Quaternion operator+(const Quaternion& rhs) const;
        inline Quaternion operator-(const Quaternion& rhs) const;


        void printString() const;
        
    };

    
}
#endif // !QUATERNION_H