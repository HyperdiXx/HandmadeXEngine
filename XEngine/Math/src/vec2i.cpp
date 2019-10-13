#include "vec2i.h"

namespace Math
{

    inline real32 vec2i::length() const
    {
        return sqrtf(lengthSqr());
    }

    inline int32 vec2i::lengthSqr() const
    {
        return x * x + y * y;
    }

    inline vec2i vec2i::operator+(const vec2i &b)
    {
        return vec2i(x + b.x, y + b.y);
    }

    inline vec2i vec2i::operator+(const int32& b)
    {
        return vec2i(x + b, y + b);
    }

    inline vec2i vec2i::operator-(const vec2i &b)
    {
        return vec2i(x - b.x, y - b.y);
    }

    inline vec2i vec2i::operator-(const int32& b)
    {
        return vec2i(x - b, y - b);
    }


    inline vec2i vec2i::operator*(const int32 &val)
    {
        return vec2i(x * val, y * val);
    }

    inline vec2i vec2i::operator*(const vec2i &b)
    {
        return vec2i(x * b.x, y * b.y);
    }

    inline vec2i vec2i::operator/(const vec2i &b)
    {
        return vec2i(x / b.x, y / b.y);
    }

    inline vec2i vec2i::operator/(const int32 & val)
    {
        return vec2i(x / val, y / val);
    }

    inline bool vec2i::operator==(const vec2i& a)
    {
        return x == a.x && y == a.y;
    }

    inline bool vec2i::operator!=(const vec2i& a)
    {
        return !(*this == a);
    }

    inline vec2i& vec2i::operator+=(const vec2i& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    inline vec2i& vec2i::operator-=(const vec2i& a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    inline vec2i& vec2i::operator*=(const vec2i& a)
    {
        x *= a.x;
        y *= a.y;
        return *this;
    }

    inline vec2i& vec2i::operator/=(const vec2i& a)
    {
        x /= a.x;
        y /= a.y;
        return *this;
    }
}
