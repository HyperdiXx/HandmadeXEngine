#include "vec2f.h"

namespace Math
{

    // functions 

    inline vec2f vec2f::operator+(const vec2f & b)
    {
        return vec2f(x + b.x, y + b.y);
    }

    inline vec2f vec2f::operator+(const real32& val)
    {
        return vec2f(x + val, y + val);
    }

    inline vec2f vec2f::operator-(const vec2f &b)
    {
        return vec2f(x - b.x, y - b.y);
    }

    inline vec2f vec2f::operator-(const real32& val)
    {
        return vec2f(x - val, y - val);
    }

    inline vec2f vec2f::operator*(const real32 &val)
    {
        return vec2f(x * val, y * val);
    }

    inline vec2f vec2f::operator*(const vec2f& b)
    {
        return vec2f(x * b.x, y * b.y);
    }

    inline vec2f& vec2f::operator+=(const vec2f& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    inline vec2f& vec2f::operator-=(const vec2f& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    inline vec2f& vec2f::operator*=(const vec2f& a)
    {
        x *= a.x;
        y *= a.y;
        return *this;
    }

    inline vec2f& vec2f::operator/=(const vec2f& a)
    {
        x /= a.x;
        y /= a.y;
        return *this;
    }

    inline vec2f vec2f::operator-() const
    {
        return vec2f(-x, -y);
    }

    inline bool vec2f::operator<(const vec2f & other) const
    {
        return x < other.x && y < other.y;
    }

    inline bool vec2f::operator<=(const vec2f & other) const
    {
        return x <= other.x && y <= other.y;
    }

    inline bool vec2f::operator>(const vec2f & other) const
    {
        return x > other.x && y > other.y;
    }

    inline bool vec2f::operator>=(const vec2f & other) const
    {
        return x >= other.x && y >= other.y;
    }

    inline bool vec2f::operator==(const vec2f& a)
    {
        return x == a.x && y == a.y;
    }

    inline bool vec2f::operator!=(const vec2f& a)
    {
        return !(*this == a);
    }

    inline real32 vec2f::length() const
    {
        return sqrtf(lengthSqr());
    }

    inline real32 vec2f::lengthSqr() const
    {
        return x * x + y * y;
    }

    inline bool vec2f::equals(const vec2f & b, real32 tolerance = SMALL_NUMBER)
    {
        return abs(x - b.x) <= tolerance && abs(y - b.y) <= tolerance;
    }

    inline void vec2f::normalize()
    {
        real32 sqrS = x * x + y * y;

        if (sqrS > SMALL_NUMBER)
        {
            real32 s = MathGeneral::InvSqrt(sqrS);

            x *= s;
            y *= s;
        }

        x = 0.0f;
        y = 0.0f;
    }

    inline bool vec2f::isZero() const
    {
        return x == 0.0f && y == 0.0f;
    }

    inline void vec2f::set(const real32 a, const real32 b)
    {
        x = a;
        y = b;
    }

    inline void vec2f::set(const vec2f & b)
    {
        x = b.x;
        y = b.y;
    }

    inline real32 vec2f::getMin() const
    {
        return Utils::min(x, y);
    }

    inline real32 vec2f::getMax() const
    {
        return Utils::max(x, y);
    }

    inline real32 vec2f::dotProduct(const vec2f & a, const vec2f & b)
    {
        return a.x * b.x + a.y * b.y;
    }

    inline real32 vec2f::crossProduct(const vec2f & a, const vec2f & b)
    {
        return a.x * b.y - a.y * b.x;
    }

    inline real32 vec2f::distance(const vec2f & a, const vec2f & b)
    {
        return sqrtf(distanceSqr(a, b));
    }

    inline real32 vec2f::distanceSqr(const vec2f & a, const vec2f & b)
    {
        return sqrtf(b.x - a.x) + sqrtf(b.y - a.y);
    }

    inline vec2f vec2f::max(const vec2f & a, const vec2f & b)
    {
        return vec2f(Utils::max(a.x, b.x), Utils::max(a.y, b.y));
    }

    inline vec2f vec2f::min(const vec2f & a, const vec2f &b)
    {
        return vec2f(Utils::min(a.x, b.x), Utils::min(a.y, b.y));
    }

}