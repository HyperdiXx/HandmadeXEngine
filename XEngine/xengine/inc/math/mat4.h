#pragma once

#ifndef MAT4_H
#define MAT4_H

#include "vec3f.h"
#include "vec4f.h"
#include "utils.h"

struct mat4
{
    static const int32 ELEM_COUNT = 16;
    static const int32 ROW_COUNT = 4;

    /**
     *   Row-major notation matrix 4x4 real32 val
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

        vec4f column[ROW_COUNT];
    };

    //Default Constructor. Creates Zero Matrix
    mat4()
    {
        for (size_t i = 0; i < ELEM_COUNT; ++i)
            elem[i] = 0.0f;
    }

    mat4(const mat4& mat)
    {
        for (size_t i = 0; i < ELEM_COUNT; ++i)
            elem[i] = mat.elem[i];
    }

    mat4(mat4 && mat) noexcept
    {
        for (size_t i = 0; i < ELEM_COUNT; ++i)
            elem[i] = mat.elem[i];
    }

    //Creates identity Matrix
    mat4(real32 iden)
    {
        for (size_t i = 0; i < ELEM_COUNT; ++i)
            elem[i] = 0.0f;

        elem[0] = iden;
        elem[1 + 1 * ROW_COUNT] = iden;
        elem[2 + 2 * ROW_COUNT] = iden;
        elem[3 + 3 * ROW_COUNT] = iden;
    }

    mat4(real32 m00, real32 m01, real32 m02, real32 m03,
        real32 m10, real32 m11, real32 m12, real32 m13,
        real32 m20, real32 m21, real32 m22, real32 m23,
        real32 m30, real32 m31, real32 m32, real32 m33)
    {
        elem[0] = m00;
        elem[1] = m01;
        elem[2] = m02;
        elem[3] = m03;

        elem[4] = m10;
        elem[5] = m11;
        elem[6] = m12;
        elem[7] = m13;

        elem[8] = m20;
        elem[9] = m21;
        elem[10] = m22;
        elem[11] = m23;

        elem[12] = m30;
        elem[13] = m31;
        elem[14] = m32;
        elem[15] = m33;
    }

    void set(int32 i, real32 val);
    void set(int32 i, int32 j, real32 val);
    real32 get(int32 i) const;
    real32 get(int32 i, int32 j) const;

    int32 getIndex(int32 val) const;

    inline void zero();
    inline void transpose();
    inline mat4 getTransposed();

    inline mat4 invert() const;
    inline mat4 getInverted();

    real32 determinant();

    bool isZero() const;
    bool isIdentity() const;

    void setDiagonal(const vec4f& diagonal);
    void setDiagonal(real32 r0, real32 r1, real32 r2, real32 r3);
    void setDiagonal(real32 m1, real32 m2, real32 m3);

    inline vec3f getTranslation() const { return vec3f(m03, m13, m23); }
    inline void setTranslation(const vec3f& a) { m03 = a.x; m13 = a.y; m23 = a.z; }

    void printElements() const
    {
        printf("\nMatrix 4x4\n");
        for (size_t i = 0; i < ELEM_COUNT; i = i + 4)
        {
            printf("%f %f %f %f\n", elem[i], elem[i + 1], elem[i + 2], elem[i + 3]);
        }
        printf("\n");
    }

    static mat4 identity()
    {
        return mat4(1.0f);
    }

    mat4& mul(const mat4& a)
    {
        real32 data[ELEM_COUNT];

        for (size_t y = 0; y < ROW_COUNT; ++y)
        {
            for (size_t x = 0; x < ROW_COUNT; ++x)
            {
                real32 s = 0.0f;
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

    real32 operator[](int i) const;

    bool operator==(const mat4& rhs) const;
    mat4& operator=(const mat4& rhs);
    bool operator!=(const mat4& rhs) const;

    mat4 operator+(const mat4& rhs) const;

    mat4& operator+=(const mat4& rhs);

    mat4 operator-(const mat4& rhs) const;

    mat4 operator-=(const mat4& rhs);

    mat4 operator*(const mat4& rhs) const;

    mat4 operator*=(const mat4& rhs);

    mat4 operator*(const real32 scalar) const;

    mat4 operator*=(const real32 scalar);

    //vec4f operator*(const vec4f& r);

    static mat4 ortho(real32 left, real32 right, real32 top, real32 bottom, real32 nearplane, real32 farplane);

    static mat4 perspective(real32 fov, real32 aspectratio, real32 nearplane, real32 farplane);

    static mat4 translate(const vec3f &tran);
    static mat4 rotate(real32 angle, const vec3f& axis);
    static mat4 scale(const vec3f& scale);

    static mat4 rotateRes(const vec3f& rotationVec);
    static mat4 rotateX(real32 radians);
    static mat4 rotateY(real32 radians);
    static mat4 rotateZ(real32 radians);

    static mat4 transform(const vec3f& translate, const vec3f& rotate, const vec3f& scale);

    std::string toString() const;
};

#endif // !MAT3_H
