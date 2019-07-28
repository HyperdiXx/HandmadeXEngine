#pragma once

#include "mat4.h"
#include "vec3.h"
#include "utils.h"

namespace Math
{
    /**
      * Quaternion represents 3d rotations
      *
      *
      */
    class Quaternion
    {
    public:
        static const Quaternion identity;

        union
        {
            struct
            {
                float x, y, z, w;               
            };
            float data[4];
        };

        inline Quaternion(const float *data);
        inline Quaternion(float xV = 0.0f, float yVal = 0.0f, float zVal = 0.0f, float wVal = 1.0f);
        inline Quaternion(const Quaternion& b);
        inline const Quaternion& operator=(const Quaternion& b);
        
        inline Quaternion& operator*=(const Quaternion& quat);
        inline Quaternion operator*(const Quaternion& q) const;

        inline bool operator==(Quaternion& b) const;
        inline bool operator!=(const Quaternion& b) const;

        inline mat4 getMatrix() const;
        inline void getMatrix(mat4* mat) const;
        inline Quaternion getInverse() const;
        inline vec3 getEulerAngle() const;

        inline void inverse();
        inline void transpose();
        inline void normalize();
        inline float length() const;

        inline static Quaternion rotate(const vec3& euler);
        inline static Quaternion rotate(const mat4& matrix);
        inline static Quaternion rotate(const vec3& source, const vec3& dest, const vec3& r = vec3(0.0f, 0.0f, 0.0f));
        inline static Quaternion rotate(const vec3& vec, float angle);
        
        inline static Quaternion rotateFast();
        inline static Quaternion rotateFast();
        inline static Quaternion rotateFast();
        inline static Quaternion rotateFast();

        //Convertion
        inline void convertToAxisAngle(vec3& vec, float& angle) const;

        inline void multiply(const Quaternion& a, Quaternion& b) const;

        inline float dot(const Quaternion& a) const;
        inline void slerp(const Quaternion& q1, const Quaternion& q2, float t);

        inline vec3 addToVec(const vec3& vec) const;

        inline void construct(const vec3& euler);
        inline void construct(const vec3& vec, float angle);
        inline void construct(const mat4& matrix);
        inline void construct(const vec3& source, const vec3& dest, const vec3& r = vec3(0.0f, 0.0f, 0.0f));
    };
}