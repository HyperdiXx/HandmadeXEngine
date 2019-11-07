#include "vec2f.h"

    // functions 

    vec2f vec2f::operator+(const vec2f & b)
    {
        return vec2f(x + b.x, y + b.y);
    }

    vec2f vec2f::operator+(const real32& val)
    {
        return vec2f(x + val, y + val);
    }

    vec2f vec2f::operator-(const vec2f &b)
    {
        return vec2f(x - b.x, y - b.y);
    }

    vec2f vec2f::operator-(const real32& val)
    {
        return vec2f(x - val, y - val);
    }

    vec2f vec2f::operator*(const real32 &val)
    {
        return vec2f(x * val, y * val);
    }

    vec2f vec2f::operator*(const vec2f& b)
    {
        return vec2f(x * b.x, y * b.y);
    }

    vec2f& vec2f::operator+=(const vec2f& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    vec2f& vec2f::operator-=(const vec2f& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    vec2f& vec2f::operator*=(const vec2f& a)
    {
        x *= a.x;
        y *= a.y;
        return *this;
    }

    vec2f& vec2f::operator/=(const vec2f& a)
    {
        x /= a.x;
        y /= a.y;
        return *this;
    }

    vec2f vec2f::operator-() const
    {
        return vec2f(-x, -y);
    }

    bool vec2f::operator<(const vec2f & other) const
    {
        return x < other.x && y < other.y;
    }

    bool vec2f::operator<=(const vec2f & other) const
    {
        return x <= other.x && y <= other.y;
    }

    bool vec2f::operator>(const vec2f & other) const
    {
        return x > other.x && y > other.y;
    }

    bool vec2f::operator>=(const vec2f & other) const
    {
        return x >= other.x && y >= other.y;
    }

    bool vec2f::operator==(const vec2f& a)
    {
        return x == a.x && y == a.y;
    }

    bool vec2f::operator!=(const vec2f& a)
    {
        return !(*this == a);
    }

    real32 vec2f::length() const
    {
        return sqrtf(lengthSqr());
    }

    real32 vec2f::lengthSqr() const
    {
        return x * x + y * y;
    }

    bool vec2f::equals(const vec2f & b, real32 tolerance = SMALL_NUMBER)
    {
        return abs(x - b.x) <= tolerance && abs(y - b.y) <= tolerance;
    }

    void vec2f::normalize()
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

    bool vec2f::isZero() const
    {
        return x == 0.0f && y == 0.0f;
    }

    void vec2f::set(const real32 a, const real32 b)
    {
        x = a;
        y = b;
    }

    void vec2f::set(const vec2f & b)
    {
        x = b.x;
        y = b.y;
    }

    real32 vec2f::getMin() const
    {
        return Utils::minVal(x, y);
    }

    real32 vec2f::getMax() const
    {
        return Utils::maxVal(x, y);
    }

    real32 vec2f::dotProduct(const vec2f & a, const vec2f & b)
    {
        return a.x * b.x + a.y * b.y;
    }

    real32 vec2f::crossProduct(const vec2f & a, const vec2f & b)
    {
        return a.x * b.y - a.y * b.x;
    }

    real32 vec2f::distance(const vec2f & a, const vec2f & b)
    {
        return sqrtf(distanceSqr(a, b));
    }

    real32 vec2f::distanceSqr(const vec2f & a, const vec2f & b)
    {
        return sqrtf(b.x - a.x) + sqrtf(b.y - a.y);
    }

    vec2f vec2f::maxCmp(const vec2f & a, const vec2f & b)
    {
        return vec2f(Utils::maxVal(a.x, b.x), Utils::maxVal(a.y, b.y));
    }

    vec2f vec2f::minCmp(const vec2f & a, const vec2f &b)
    {
        return vec2f(Utils::minVal(a.x, b.x), Utils::minVal(a.y, b.y));
    }
