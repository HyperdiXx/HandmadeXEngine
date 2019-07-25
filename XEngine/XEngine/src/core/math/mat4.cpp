#include "mat4.h"
#include "math.h"

namespace Math
{
    mat4 mat4::translation(const vec3 &tran)
    {
        mat4 res(1.0f);

        res.elem[0 + 3 * 4] = tran.x;
        res.elem[1 + 3 * 4] = tran.y;
        res.elem[2 + 3 * 4] = tran.z;

        return (res);
    }

    mat4 mat4::rotation(float angle, const vec3 & axis)
    {
        mat4 res(1.0f);

        float r = toRadians(angle);
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
    
}
