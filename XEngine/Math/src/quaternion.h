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
    class MATH_API Quaternion
    {
    public:
        static const Quaternion identity;

        union
        {
            struct
            {
                real32 x, y, z, w;               
            };
            real32 data[4];
        };

        inline Quaternion(const real32 *data) {};
        inline Quaternion(real32 xV = 0.0f, real32 yVal = 0.0f, real32 zVal = 0.0f, real32 wVal = 1.0f) {};
        inline Quaternion(const Quaternion& b) {};

        inline mat4 getMatrix() const;
        inline void getMatrix(mat4* mat) const;
        inline Quaternion getInverse() const;
        inline vec3 getEulerAngle() const;

        inline void invert();
        inline void normalize(real32 tolerance = TOLERANCE);

        inline real32 length() const;
        inline real32 lengthSqr() const;

        inline bool isNormalized() const;

        inline Quaternion getInverted();
        inline Quaternion getNormalized() const;

        inline static Quaternion rotate(const vec3& euler);
        inline static Quaternion rotate(const mat4& matrix);
        inline static Quaternion rotate(const vec3& src, const vec3& dest, const vec3& r = vec3(0.0f, 0.0f, 0.0f));
        inline static Quaternion rotate(const vec3& vec, real32 angle);
        
        inline static Quaternion rotateFast(const vec3& euler);
        inline static Quaternion rotateFast(const mat4& matrix);
        inline static Quaternion rotateFast(const vec3& vec, real32 angle);
        inline static Quaternion rotateFast(const vec3& src, const vec3& dest, const vec3& r = vec3(0.0f, 0.0f, 0.0f));

        //Convertion
        inline void convertToAxisAngle(vec3& vec, real32& angle) const;

        inline void multiply(const Quaternion& a, Quaternion& b) const;

        inline real32 dot(const Quaternion& a) const;
        inline Quaternion slerp(const Quaternion& q1, const Quaternion& q2, real32 t);
        inline Quaternion nlerp(const Quaternion& q1, const Quaternion& q2, real32 t);

        inline vec3 addToVec(const vec3& vec) const;

        inline void constructFromEulerAngles(const vec3& euler);
        inline void constructFromVecAngle(const vec3& vec, real32 angle);
        inline void constructFromMatrix(const mat4& matrix);
        inline void constructFromVecs(const vec3& source, const vec3& dest, const vec3& r = vec3(0.0f, 0.0f, 0.0f));

        /**
        * Operators 
        */
        inline const Quaternion& operator=(const Quaternion& b);
        inline Quaternion& operator*=(const Quaternion& quat);
        inline Quaternion operator*(const Quaternion& q) const;

        inline bool operator==(Quaternion& b) const;
        inline bool operator!=(const Quaternion& b) const;



    };

    // Optimize
    inline void Quaternion::normalize(real32 tolerance)
    {
        real32 sqrSum = x * x + y * y + z * z + w * w;
        
        if (sqrSum >= tolerance)
        {
            const real32 scale = MathGeneral::InvSqrt(sqrSum);

            x *= scale;
            y *= scale;
            z *= scale;
            w *= scale;

        }
        else
            *this = Quaternion::identity;
    }

    inline real32 Quaternion::length() const
    {
        return x * x + y * y + z * z + w * w;
    }

    inline real32 Quaternion::lengthSqr() const
    {
        return MathGeneral::Sqrt(length());
    }

    inline bool Quaternion::isNormalized() const
    {
        return (MathGeneral::Abs(1.f - length()) < THRESH_QUAT_NORMALIZED);
    }

    inline Quaternion Quaternion::getInverted()
    {
        if(!isNormalized())
            normalize();

        return Quaternion(-x, -y, -z, w);
    }

    inline Quaternion Quaternion::getNormalized() const
    {
        Quaternion quat;

        real32 len = length();

        quat.x /= len;
        quat.y /= len;
        quat.z /= len;
        quat.w /= len;

        return quat;
    }



}
#endif // !QUATERNION_H