#include "vec4f.h"

namespace Math
{
    inline vec4f vec4f::operator+(const vec4f& a) const
    {
        return vec4f(x + a.x, y + a.y, z + a.z, w + a.w);        
    }

    inline vec4f vec4f::operator-(const vec4f& a) const
    {
       return vec4f(x - a.x, y - a.y, z - a.z, w + a.w);
    }

    inline vec4f vec4f::operator*(const vec4f& a) const
    {
       return vec4f(x * a.x, y * a.y, z * a.z, w * a.w);
    }

    inline vec4f vec4f::operator*(real32 a) const
    {
        return vec4f(x * a, y * a, z * a, w * a);
    }

    inline vec4f& vec4f::operator*=(const real32 scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    inline vec4f vec4f::operator/(const vec4f & a) const
    {
        return vec4f(x / a.x, y / a.y, z / a.z, w / a.w);
    }

    inline bool vec4f::operator==(const vec4f & a)
    {
        return x == a.x && y == a.y && z == a.z && w == a.w;
    }

    inline bool vec4f::operator!=(const vec4f & a)
    {
        return !(*this == a);
    }

    inline vec4f & vec4f::operator+=(const vec4f & a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        w += a.w;
        return *this;
    }

    inline vec4f & vec4f::operator-=(const vec4f & a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        w -= a.w;
        return *this;
    }

    inline vec4f & vec4f::operator=(const vec4f & a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
        w = a.w;
        return *this;
    }

    inline vec4f & vec4f::operator=(vec4f && a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
        w = a.w;
        return *this;
    }

    inline vec4f & vec4f::operator*=(const vec4f & a)
    {
        x *= a.x;
        y *= a.y;
        z *= a.z;
        w *= a.w;
        return *this;
    }

    inline vec4f vec4f::operator/(real32 a) const
    {
        return vec4f(x / a, y / a, z / a, w / a);
    }

    inline vec4f& vec4f::operator/=(const vec4f & a)
    {
        x /= a.x;
        y /= a.y;
        z /= a.z;
        w /= a.w;
        return *this;
    }

    vec4f vec4f::getNormalized(real32 tolerance)
    {
        const real32 sqrSum = x * x + y * y + z * z;
        if (sqrSum > tolerance)
        {
            const real32 scale = MathGeneral::InvSqrt(sqrSum);
            return vec4f(x * scale, y * scale, z * scale, 0.0f);
        }
        return vec4f();
    }

    inline real32 vec4f::getMagnitude() const
    {
        return sqrtf(sqrMagnitude());
    }

    inline void vec4f::normalize()
    {
        real32 length = getMagnitude();
        x /= length;
        y /= length;
        z /= length;
        w /= length;

    }

    inline real32 vec4f::sqrMagnitude() const
    {
        return x * x + y * y + z * z + w * w;
    }

    real32 vec4f::distance(vec4f& s, vec4f& e)
    {
        return (s - e).getMagnitude();
    }

    vec4f vec4f::lerp(const vec4f& start, const vec4f& end, real32 t)
    {
        return (start * (1.0f - t)) + end * t;
    }

    real32 vec4f::dot(const vec4f & a, const vec4f & b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }


}