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
        union
        {
            struct
            {
                // m[row][column]
                float m11, m21, m31, m41, m12, m22, m32, m42, m13, m23, m33, m43, m14, m24, m34, m44;
            };
            float	elem[16];
            vec4<float> column[4];
        };

        mat4()
        {
            for (size_t i = 0; i < 16; ++i)
                elem[i] = 0.0f;
        }
        mat4(float iden)
        {
            for (size_t i = 0; i < 16; ++i)
                elem[i] = 0.0f;

            elem[0] = iden;
            elem[1 + 1 * 4] = iden;
            elem[2 + 2 * 4] = iden;
            elem[3 + 3 * 4] = iden;
        }

        static mat4 identity()
        {
            return mat4(1.0f);
        }

        mat4& mul(const mat4& a)
        {
            float data[16];

            for (size_t y = 0; y < 4; ++y)
            {
                for (size_t x = 0; x < 4; ++x)
                {
                    float s = 0.0f;
                    for (size_t el = 0; el < 4; ++el)
                    {
                        s += elem[x + el * 4] * a.elem[el + y * 4];
                    }
                    data[x + y * 4] = s;
                }
            }

            memcpy(elem, data, 16);

            return *this;
        }

        static mat4 ortho(float left, float right, float top, float bottom, float nearplane, float farplane)
        {
            mat4 res(1.0f);

            res.elem[0 + 0 * 4] = 2.0f / (right - left);
            res.elem[1 + 1 * 4] = 2.0f / (top - bottom);
            res.elem[2 + 2 * 4] = 2.0f / (nearplane - farplane);

            res.elem[0 + 3 * 4] = (left + right) / (left - right);
            res.elem[1 + 3 * 4] = (bottom + top) / (top - bottom);
            res.elem[2 + 3 * 4] = (farplane + nearplane) / (farplane - nearplane);

            return res;

        }

        static mat4 perspective(float fov, float aspectratio, float nearplane, float farplane)
        {
            mat4 res;

            float q = 1.0f / tan(toRadians(0.5f * fov));
            float a = q / aspectratio;
            float b = (nearplane + farplane) / (nearplane - farplane);
            float c = (2.0f  * nearplane * farplane) / (nearplane - farplane);
            res.elem[0 + 0 * 4] = a;
            res.elem[1 + 1 * 4] = q;
            res.elem[2 + 2  * 4] = b;
            res.elem[3 + 2  * 4] = -1.0f;
            res.elem[2 + 3  * 4] = c;

            return res;
        }

        static mat4 translation(const vec3 &tran);
        static mat4 rotation(float angle, const vec3& axis);
        static mat4 scale(const vec3& scale);

        friend mat4 operator*(mat4& a, const mat4& b)
        {
            return a.mul(b);           
        };

        mat4& operator*=(const mat4& a)
        {
            return mul(a);
        }

    };
}
#endif // !MAT3_H
