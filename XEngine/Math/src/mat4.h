#pragma once

#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"
#include "utils.h"

namespace Math
{
    struct MATH_API mat4
    {
        static const int32 ELEM_COUNT = 16;
        static const int32 ROW_COUNT = 4;

        /**
         *   Row-major notation matrix 4x4 float val
         *
         *   [m00, m01, m02, m03,
         *    m10, m11, m12, m13,
         *    m20, m21, m22, m23,
         *    m30, m31, m32, m33]
         */

        union
        {
            struct
            {
                // m[row][column]
               
                real32 m00, m01, m02, m03;
                real32 m10, m11, m12, m13;
                real32 m20, m21, m22, m23;
                real32 m30, m31, m32, m33;

            };
            real32	elem[16];

            vec4<real32> column[ROW_COUNT];
        };

        //Default Constructor. Creates Zero Matrix
        mat4()
        {
            for (size_t i = 0; i < ELEM_COUNT; ++i)
                elem[i] = 0.0f;
        }

        //Identity Constructor. Creates identity Matrix
        mat4(real32 iden)
        {
            for (size_t i = 0; i < ELEM_COUNT; ++i)
                elem[i] = 0.0f;

            elem[0] = iden;
            elem[1 + 1 * ROW_COUNT] = iden;
            elem[2 + 2 * ROW_COUNT] = iden;
            elem[3 + 3 * ROW_COUNT] = iden;
        }

        void set(int32 i, real32 val);
        void set(int32 i, int32 j, real32 val);
        real32 get(int32 i) const;
        real32 get(int32 i, int32 j) const;

        int32 getIndex(int32 val) const;

        inline void zero();
        inline mat4 transpose() const;

        inline mat4* getTransposed();

        inline mat4 invert() const;
        inline mat4 getInverted();

        float determinant();

        bool isZero() const;
        bool isIdentity() const;
   
        void setDiagonal(const vec4<real32>& diagonal);
        void setDiagonal(real32 r0, real32 r1, real32 r2, real32 r3);
        void setDiagonal(real32 m1, real32 m2, real32 m3);

        static mat4 identity()
        {
            return mat4(1.0f);
        }

        mat4& mul(const mat4& a)
        {
            float data[ELEM_COUNT];

            for (size_t y = 0; y < ROW_COUNT; ++y)
            {
                for (size_t x = 0; x < ROW_COUNT; ++x)
                {
                    float s = 0.0f;
                    for (size_t el = 0; el < ROW_COUNT; ++el)
                    {
                        s += elem[x + el * ROW_COUNT] * a.elem[el + y * ROW_COUNT];
                    }
                    data[x + y * ROW_COUNT] = s;
                }
            }

            memcpy(elem, data, ELEM_COUNT);

            return *this;
        }

        float operator[](int i) const;

        bool operator==(const mat4& rhs) const;

        bool operator!=(const mat4& rhs) const;

        mat4 operator+(const mat4& rhs) const;

        mat4& operator+=(const mat4& rhs);

        mat4 operator-(const mat4& rhs) const;

        mat4 operator-=(const mat4& rhs);

        mat4 operator*(const mat4& rhs) const;

        mat4 operator*=(const mat4& rhs);

        mat4 operator*(const float scalar) const;

        mat4 operator*=(const float scalar);
        
        vec4<float> operator*(const vec4<float> & r);

        static mat4 ortho(float left, float right, float top, float bottom, float nearplane, float farplane)
        {
            mat4 res(1.0f);

            res.elem[0 + 0 * ROW_COUNT] = 2.0f / (right - left);
            res.elem[1 + 1 * ROW_COUNT] = 2.0f / (top - bottom);
            res.elem[2 + 2 * ROW_COUNT] = 2.0f / (nearplane - farplane);

            res.elem[0 + 3 * ROW_COUNT] = (left + right) / (left - right);
            res.elem[1 + 3 * ROW_COUNT] = (bottom + top) / (top - bottom);
            res.elem[2 + 3 * ROW_COUNT] = (farplane + nearplane) / (farplane - nearplane);

            return res;

        }

        static mat4 perspective(float fov, float aspectratio, float nearplane, float farplane)
        {
            mat4 res;

            float q = 1.0f / tan(Utils::toRadians(0.5f * fov));
            float a = q / aspectratio;
            float b = (nearplane + farplane) / (nearplane - farplane);
            float c = (2.0f  * nearplane * farplane) / (nearplane - farplane);
            res.elem[0 + 0 * ROW_COUNT] = a;
            res.elem[1 + 1 * ROW_COUNT] = q;
            res.elem[2 + 2 * ROW_COUNT] = b;
            res.elem[3 + 2 * ROW_COUNT] = -1.0f;
            res.elem[2 + 3 * ROW_COUNT] = c;

            return res;
        }

        static mat4 translate(const vec3 &tran);
        static mat4 rotate(float angle, const vec3& axis);
        static mat4 scale(const vec3& scale);

        static mat4 rotateRes(const vec3& rotationVec);
        static mat4 rotateX(float radians);
        static mat4 rotateY(float radians);
        static mat4 rotateZ(float radians);

        static mat4 transform(const vec3& translate, const vec3& rotate, const vec3& scale);

    };
}
#endif // !MAT3_H
