#pragma once

#ifndef GEN_MATH
#define GEN_MATH

#include "types.h"

#include <random>

#define THRESH_QUAT_NORMALIZED 0.01f
#define TOLERANCE 0.00000001f

struct MathGeneral
{
    inline static int32 truncToInt(real32 val)
    {
        return (int32)val;
    }

    inline static real32 truncToFloat(real32 val)
    {
        return (real32)val;
    }

    inline static real32 floatToFloat(real32 val)
    {
        return floorf(val);
    }

    inline static int32 floorToInt(real32 val)
    {
        return truncToInt(floorf(val));
    }

    inline static int32 roundToInt(real32 val)
    {
        return floorToInt(val + 0.5f);
    }

    inline static real32 floorToFloat(real32 val)
    {
        return floorf(val);
    }

    inline static real64 floorToDouble(real32 val)
    {
        return floor(val);
    }

    inline static real32 roundToFloat(real32 val)
    {
        return floorToFloat(val + 0.5f);
    }

    inline static real32 ceilToFloat(real32 val)
    {
        return ceilf(val);
    }

    inline static real64 ceiltToDouble(real64 val)
    {
        return ceil(val);
    }

    inline static real32 getFractionalSigned(real32 val)
    {
        return val - truncToFloat(val);
    }

    inline static real32 getFractional(real32 val)
    {
        return val - floorToFloat(val);
    }

    inline static real32 getMod(const real32 in, real32 *out)
    {
        return modff(in, out);
    }

    inline static real32 exp(real32 val)
    {
        return expf(val);
    }

    inline static real32 log(real32 val)
    {
        return logf(val);
    }

    inline static real32 Sin(real32 radians)
    {
        return sinf(radians);
    }

    inline static real32 Cos(real32 radians)
    {
        return cosf(radians);
    }

    /** Inverse square root */
    inline static real32 InvSqrt(real32 F)
    {
        return 1.0f / sqrtf(F);
    }

    inline static real32 Asin(real32 val) { return asinf((val < -1.0f) ? -1.0f : ((val < 1.0f) ? val : 1.0f)); }
    inline static real32 Sinh(real32 val) { return sinhf(val); }
    inline static real32 Acos(real32 val) { return acosf((val < -1.0f) ? -1.0f : ((val < 1.0f) ? val : 1.0f)); }
    inline static real32 Tan(real32 val) { return tanf(val); }
    inline static real32 Atan(real32 val) { return atanf(val); }
    inline static real32 Sqrt(real32 val) { return sqrtf(val); }
    inline static real32 Pow(real32 a, real32 b) { return powf(a, b); }

    inline static int32 Rand() { return rand(); }
    inline static void Srand(int32 val) { return srand(val); }
};

#endif // !GEN_MATH

