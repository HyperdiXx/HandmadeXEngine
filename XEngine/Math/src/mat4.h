#pragma once

#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"
#include "vec4.h"
#include "utils.h"

namespace Math
{
    struct MATH_API mat4
    {
        static const int ELEM_COUNT = 16;
        static const int ROW_COUNT = 4;

        union
        {
            struct
            {
                // m[row][column]
                float m11, m21, m31, m41, m12, m22, m32, m42, m13, m23, m33, m43, m14, m24, m34, m44;
            };
            float	elem[16];

            vec4<float> column[ROW_COUNT];
        };

        mat4()
        {
            for (size_t i = 0; i < ELEM_COUNT; ++i)
                elem[i] = 0.0f;
        }
        mat4(float iden)
        {
            for (size_t i = 0; i < ELEM_COUNT; ++i)
                elem[i] = 0.0f;

            elem[0] = iden;
            elem[1 + 1 * ROW_COUNT] = iden;
            elem[2 + 2 * ROW_COUNT] = iden;
            elem[3 + 3 * ROW_COUNT] = iden;
        }

        void set(int i, float val);
        void set(int i, int j, float val);
        float get(int i) const;
        float get(int i, int j) const;

        int getIndex(int val) const;

        mat4 transpose() const;

        mat4 inverse() const;

        float determinant();

        bool isZero() const;
        bool isIdentity() const;
   
        void setDiagonal(const vec4<float>& diagonal);
        void setDiagonal(float r0, float r1, float r2, float r3);
        void setDiagonal(float m1, float m2, float m3);

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
