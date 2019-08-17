#include "mat4.h"
#include "math.h"

namespace Math
{
    mat4 mat4::translate(const vec3 &tran)
    {
        mat4 res(1.0f);

        res.elem[0 + 3 * 4] = tran.x;
        res.elem[1 + 3 * 4] = tran.y;
        res.elem[2 + 3 * 4] = tran.z;

        return (res);
    }

    mat4 mat4::rotate(float angle, const vec3 & axis)
    {
        mat4 res(1.0f);

        float r = Utils::toRadians(angle);
        float c = cos(r);
        float s = sin(r);

        float x = axis.x;
        float y = axis.y;
        float z = axis.z;
        float o = 1.0f - c;

        res.elem[0 + 0 * 4] = x * o + c;
        res.elem[1 + 0 * 4] = y * x * o + z * s;
        res.elem[2 + 0 * 4] = x * z * o - y * s;

        res.elem[0 + 1 * 4] = x * y * o - z * c;
        res.elem[1 + 1 * 4] = y * o + c;
        res.elem[2 + 1 * 4] = y * z * o + x * s;

        res.elem[0 + 2 * 4] = x * z * o + y * s;
        res.elem[1 + 2 * 4] = y * z * o - x * s;
        res.elem[2 + 2 * 4] = z * o + c;

        return (res);
    }

    mat4 mat4::scale(const vec3 & scale)
    {
        mat4 res(1.0f);

        res.elem[0 + 0 * 4] = scale.x;
        res.elem[1 + 1 * 4] = scale.y;
        res.elem[2 + 2 * 4] = scale.z;

        return (res);
    }

    mat4 mat4::rotateX(float radians)
    {
        mat4 res = mat4::identity();

        float cos = Utils::cos(radians);
        float sin = Utils::sin(radians);

        res.m22 = cos;
        res.m23 = sin;
        res.m32 = -sin;
        res.m33 = cos;

        return res;
    }

    mat4 mat4::rotateY(float radians)
    {
        mat4 res = mat4::identity();

        float cos = Utils::cos(radians);
        float sin = Utils::sin(radians);

        res.m11 = cos;
        res.m13 = -sin;
        res.m31 = sin;
        res.m33 = cos;

        return res;
    }

    mat4 mat4::rotateZ(float radians)
    {
        mat4 res = mat4::identity();

        float cos = Utils::cos(radians);
        float sin = Utils::sin(radians);

        res.m11 = cos;
        res.m12 = sin;
        res.m21 = -sin;
        res.m22 = cos;

        return res;
    }

    mat4 mat4::transform(const vec3 & translate, const vec3 & rotate, const vec3 & scale)
    {
        return mat4();
    }
    
    void mat4::setDiagonal(const vec4<float>& diagonal)
    {
        setDiagonal(diagonal.x, diagonal.y, diagonal.z, diagonal.z);
    }

    void mat4::setDiagonal(float m1, float m2, float m3)
    {
        setDiagonal(m1, m2, m3, 1.0f);
    }

    void mat4::setDiagonal(float r0, float r1, float r2, float r3)
    {
        m11 = r0;
        m22 = r1;
        m33 = r2;
        m44 = r3;
    }

}
