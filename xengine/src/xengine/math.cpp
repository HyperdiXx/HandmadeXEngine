
#pragma once

#ifndef MATH_CPP
#define MATH_CPP

#define PI 					3.1415926535897932f	
#define SMALL_NUMBER		1.e-8f
#define DELTA			    0.00001f
#define EPSILON             0.00000001f

#define RadiansToDegrees(angle) angle * (180.0f / PI)
#define DegreesToRadians(angle) angle * (PI / 180.0f)

typedef float Degree;
typedef float Radian;

struct Vec2
{
    union
    {
        struct
        {
            real32 x, y;
        };
        real32 data[2];
    };
};


inline Vec2 operator*(Vec2 a, real32 b) { return { a.x * b, a.y * b }; };
inline Vec2 operator*(real32 b, Vec2 a) { return { a.x * b, a.y * b }; };
inline Vec2 operator*(Vec2 a, Vec2 b) { return { a.x * b.x, a.y * b.y }; };
inline Vec2 & operator*=(Vec2& a, Vec2 b) { return a = a * b; };
inline Vec2 & operator*=(Vec2& a, real32 b) { return a = a * b; };

inline Vec2 operator+(Vec2 a, real32 b) { return { a.x + b, a.y + b }; };
inline Vec2 operator+(Vec2 a, Vec2 b) { return { a.x + b.x, a.y + b.y }; };
inline Vec2 & operator+=(Vec2& a, Vec2 b) { return a = a + b; };
inline Vec2 & operator+=(Vec2& a, real32 b) { return a = a + b; };

inline Vec2 operator-(Vec2 a) { return { -a.x, -a.y }; };
inline Vec2 operator-(Vec2 a, real32 b) { return { a.x - b, a.y - b }; };
inline Vec2 operator-(Vec2 a, Vec2 b) { return { a.x - b.x, a.y - b.y }; };
inline Vec2 & operator-=(Vec2& a, Vec2 b) { return a = a - b; };
inline Vec2 & operator-=(Vec2& a, real32 b) { return a = a - b; };

inline Vec2 operator/(Vec2 a, real32 b) { return { a.x / b, a.y / b }; };
inline Vec2 operator/(real32 b, Vec2 a) { return { b / a.x, b / a.y }; };
inline Vec2 operator/(Vec2 a, Vec2 b) { return { a.x / b.x, a.y / b.y }; };
inline Vec2 & operator/=(Vec2& a, Vec2 b) { return a = a / b; };
inline Vec2 & operator/=(Vec2& a, real32 b) { return a = a / b; };

inline bool operator==(Vec2 a, Vec2 b) { return (a.x == b.x) && (a.y == b.y); };
inline bool operator!=(Vec2 a, Vec2 b) { return !(a == b); };
inline bool operator<(Vec2 a, Vec2 b) { return (a.x < b.x) && (a.y < b.y); }
inline bool operator>(Vec2 a, Vec2 b) { return (a.x > b.x) && (a.y > b.y); }

inline real32 LengthSqr(Vec2 vec)
{
    return vec.x * vec.x + vec.y + vec.y;
}

inline real32 Length(Vec2 vec)
{
    return sqrtf(LengthSqr(vec));
}

inline real32 DotProduct(Vec2 v1, Vec2 v2)
{
    return v1.x * v2.x + v1.y + v2.y;
}

inline real32 CrossProduct(Vec2 v1, Vec2 v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

inline real32 FastInverseSqrt(real32 lSqr)
{
    const real32 threeHalfs = 1.5f;

    real32 x2 = lSqr * 0.5f;
    real32 y = lSqr;
    uint64 i = *(uint64 *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(real32 *)&i;
    y = y * (threeHalfs - (x2 * y * y));

    return y;
}

inline Vec2 Normalize(Vec2 vec)
{
    Vec2 result = {};

    real32 lengthSqr = LengthSqr(vec);
    real32 invSqr = FastInverseSqrt(lengthSqr);
    if (invSqr > 0)
    {
        result.x *= invSqr;
        result.y *= invSqr;
    }

    return result;
}

inline real32 Determinant(Vec2 v1, Vec2 v2)
{
    return CrossProduct(Normalize(v1), Normalize(v2));
}

inline Vec2 Round(Vec2 v1)
{
    return { roundf(v1.x), roundf(v1.y) };
}

inline real32 Lerp(real32 t, real32 x, real32 y)
{
    return x + t * (y - x);
}

inline Vec2 Lerp(real32 t, Vec2 min, Vec2 max)
{
    Vec2 result = {};

    result.x = Lerp(t, min.x, max.x);
    result.y = Lerp(t, min.y, max.y);

    return result;
}

inline Vec2 NormalLine(Vec2 v1, Vec2 v2)
{
    real32 diffX = v2.x - v1.x;
    real32 diffY = v2.y - v1.y;

    Vec2 result = {};

    result.x = -diffY;
    result.y = diffX;

    result = Normalize(result);

    return result;
}


struct Vec3
{
    union
    {
        struct
        {
            real32 x, y, z;
        };
        real32 data[3];
    };
};

inline Vec3 operator*(const Vec3 &a, real32 b) { return { a.x * b, a.y * b, a.z * b }; };
inline Vec3 operator*(real32 b, const Vec3 &a) { return { a.x * b, a.y * b, a.z * b }; };
inline Vec3 operator*(const Vec3 &a, const Vec3 &b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; };
inline Vec3 & operator*=(Vec3& a, const Vec3 &b) { return a = a * b; };
inline Vec3 & operator*=(Vec3& a, real32 b) { return a = a * b; };

inline Vec3 operator+(Vec3 a) { return a; };
inline Vec3 operator+(const Vec3 &a, real32 b) { return { a.x + b, a.y + b, a.z + b }; };
inline Vec3 operator+(const Vec3 &a, const Vec3 &b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; };
inline Vec3 & operator+=(Vec3& a, const Vec3 &b) { return a = a + b; };
inline Vec3 & operator+=(Vec3& a, real32 b) { return a = a + b; };

inline Vec3 operator-(Vec3 a) { return { -a.x, -a.y, -a.z }; };
inline Vec3 operator-(const Vec3 &a, real32 b) { return { a.x - b, a.y - b, a.z - b }; };
inline Vec3 operator-(const Vec3 &a, const Vec3 &b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; };
inline Vec3 & operator-=(Vec3& a, const Vec3 &b) { return a = a - b; };
inline Vec3 & operator-=(Vec3& a, real32 b) { return a = a - b; };

inline Vec3 operator/(const Vec3 &a, real32 b) { return { a.x / b, a.y / b, a.z / b }; };
inline Vec3 operator/(real32 b, const Vec3 &a) { return { b / a.x, b / a.y, b / a.z }; };
inline Vec3 operator/(const Vec3 &a, const Vec3 &b) { return { a.x / b.x, a.y / b.y, a.z / b.z }; };
inline Vec3 & operator/=(Vec3& a, const Vec3 &b) { return a = a / b; };
inline Vec3 & operator/=(Vec3& a, real32 b) { return a = a / b; };

inline bool operator==(const Vec3 &a, const Vec3 &b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); };
inline bool operator!=(const Vec3 &a, const Vec3 &b) { return !(a == b); };

inline Vec3 createVec3(real32 x, real32 y, real32 z)
{
    Vec3 res = {};

    res.x = x;
    res.y = y;
    res.z = z;

    return res;
}

inline Vec3 createVec3(const Vec3 &vec)
{
    Vec3 res = {};

    res.x = vec.x;
    res.y = vec.y;
    res.z = vec.z;

    return res;
}

inline real32 LengthSqr(Vec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

inline real32 Length(Vec3 vec)
{
    return sqrtf(LengthSqr(vec));
}

inline real32 DotProduct(const Vec3 &a, const Vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 CrossProduct(Vec3 a, Vec3 b)
{
    Vec3 res = {};

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;

    return res;
}

inline Vec3 Normalize(Vec3 vec)
{
    Vec3 result = {};

    real32 lengthSqr = LengthSqr(vec);
    real32 invSqr = FastInverseSqrt(lengthSqr);
    
    if (invSqr > 0)
    {
        result.x *= invSqr;
        result.y *= invSqr;
        result.z *= invSqr;
    }

    return result;
}

struct Vec4
{
    union
    {
        struct
        {
            real32 x, y, z, w;
        };
        real32 data[4];
    };
};

struct Vec4i
{
    union
    {
        struct
        {
            int32 x, y, z, w;
        };
        int32 data[4];
    };
};

inline Vec4 createVec4(real32 x, real32 y, real32 z, real32 w)
{
    Vec4 res = {};

    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;

    return res;
}

inline Vec4i createVec4i(int32 x, int32 y, int32 z, int32 w)
{
    Vec4i res = {};

    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;

    return res;
}

struct Rect
{
    union
    {
        struct
        {
            real32 x, y, width, height;
        };

        struct
        {
            Vec2 min, max;
        };

        real32 data[4];
    };

};

struct Vec2i
{
    union
    {
        int32 x, y;
    };

    int32 data[2];
};

inline Vec2i createVec2i(int32 x, int32 y)
{
    Vec2i res = {};

    res.x = x;
    res.y = y;

    return res;
}

struct Line
{
    union
    {
        struct
        {
            Vec2 a, b;
        };

        Vec2 data[2];
    };
};

inline bool insideRect(Rect &rect, Vec2i &p)
{
    bool isInside = p.x >= rect.min.x &&
        p.x <= rect.x + rect.max.x &&
        p.y >= rect.min.y &&
        p.y <= rect.min.y + rect.max.y;
}


inline bool rectIntersection(Rect &r1, Rect &r2)
{
    bool isIntersects = !(r2.min.x > r1.max.x ||
        r2.max.x < r1.min.x ||
        r2.max.y < r1.min.y ||
        r2.min.y > r1.max.y);
    return isIntersects;
}

struct Matrix4x4
{
    union
    {
        struct
        {
            Vec4 rows[4];           
        };

        real32 data[16];
    };
};

struct Matrix3x3
{
    union
    {
        struct
        {
            Vec4 row1;
            Vec4 row2;
            Vec4 row3;
        };

        real32 data[9];
    };
};

struct Matrix2x2
{
    union
    {
        struct
        {
            Vec4 row1;
            Vec4 row2;
        };

        real32 data[4];
    };
};

struct Quaternion
{
    union
    {
        real32 w, x, y, z;
    };

    real32 data[4];
};

struct Transform
{
    Vec3 pos;
    Quaternion quat;
    Vec2 scale;
};

inline Matrix4x4 createMat4x4()
{
    Matrix4x4 result = {};

    memset(result.data, 0, 16 * sizeof(real32));
    result.data[0 + 0 * 4] = 1.0f;
    result.data[1 + 1 * 4] = 1.0f;
    result.data[2 + 2 * 4] = 1.0f;
    result.data[3 + 3 * 4] = 1.0f;

    return result;
}

inline Matrix4x4 createMat4x4(Vec4 r1, Vec4 r2, Vec4 r3, Vec4 r4)
{
    Matrix4x4 result = {};

    memset(result.data, 0, 16 * sizeof(real32));
    
    result.rows[0] = r1;
    result.rows[1] = r2;
    result.rows[2] = r3;
    result.rows[3] = r4;
    
    return result;
}

inline Matrix4x4 createMat4x4(real32 a00, real32 a01, real32 a02, real32 a03,
                              real32 a10, real32 a11, real32 a12, real32 a13,
                              real32 a20, real32 a21, real32 a22, real32 a23,
                              real32 a30, real32 a31, real32 a32, real32 a33)
{
    Matrix4x4 result = {};

    memset(result.data, 0, 16 * sizeof(real32));

    result.data[0] = a00;
    result.data[1] = a01;
    result.data[2] = a02;
    result.data[3] = a03;

    result.data[4] = a10;
    result.data[5] = a11;
    result.data[6] = a12;
    result.data[7] = a13;

    result.data[8]  = a20;
    result.data[9]  = a21;
    result.data[10] = a22;
    result.data[11] = a23;

    result.data[12] = a30;
    result.data[13] = a31;
    result.data[14] = a32;
    result.data[15] = a33;

    return result;
}

inline Matrix3x3 createMat3x3()
{
    Matrix3x3 result = {};

    memset(result.data, 0, 9 * sizeof(real32));
    result.data[0 + 0 * 4] = 1.0f;
    result.data[1 + 1 * 4] = 1.0f;
    result.data[2 + 2 * 4] = 1.0f;

    return result;
}

inline Rect createRect(real32 x, real32 y, real32 w, real32 h)
{
    Rect result = {};

    result.min.x = x;
    result.min.y = y;
    result.max.x = w;
    result.max.y = h;

    return result;
}

inline Rect createRect(Vec2 v1, Vec2 v2)
{
    Rect result = {};

    result.min = v1;
    result.max = v2;

    return result;
}

inline Quaternion createQuat()
{
    Quaternion result = { 0.0f, 0.0f, 0.0f, 1.0f };
    return result;
}

inline Quaternion createQuat(real32 x, real32 y, real32 z, real32 w)
{
    Quaternion result = { x, y, z, w };
    return result;
}

inline Quaternion fromAxisAngle(Vec3 axis, Radian radians)
{
    Quaternion result = {};

    real32 precalc_sin = sin(radians * 0.5f);

    result.x = axis.x * precalc_sin;
    result.y = axis.y * precalc_sin;
    result.z = axis.z * precalc_sin;
    result.w = cos(radians * 0.5f);

    return result;
}

inline Quaternion fromAxisDegreeAngle(Vec3 axis, Degree degrees)
{
    return fromAxisAngle(axis, DegreesToRadians(degrees));
}

inline Quaternion operator*(const Quaternion &q1, const Quaternion &q2)
{
    Quaternion result = {};

    result.x = (q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y);
    result.y = (q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x);
    result.z = (q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w);
    result.w = (q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);

    return result;
}

inline Vec3 operator*(const Quaternion &quat, const Vec3 &vec)
{
    Vec3 res = createVec3(0.0f, 0.0f, 0.0f);

    real32 tmpX, tmpY, tmpZ, tmpW;
    
    tmpX = (((quat.w * vec.x) + (quat.y * vec.z)) - (quat.z * vec.y));
    tmpY = (((quat.w * vec.y) + (quat.z * vec.x)) - (quat.x * vec.z));
    tmpZ = (((quat.w * vec.z) + (quat.x * vec.y)) - (quat.y * vec.x));
    tmpW = (((quat.x * vec.x) + (quat.y * vec.y)) + (quat.z * vec.z));

    res.x = ((((tmpW * quat.x) + (tmpX * quat.w)) - (tmpY * quat.z)) + (tmpZ * quat.y));
    res.y = ((((tmpW * quat.y) + (tmpY * quat.w)) - (tmpZ * quat.x)) + (tmpX * quat.z));
    res.z = ((((tmpW * quat.z) + (tmpZ * quat.w)) - (tmpX * quat.y)) + (tmpY * quat.x));
    
    return res;
}

inline Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &b)
{
    Matrix4x4 res = createMat4x4();

    for (uint32 row = 0; row < 4; row++)
    {
        for (uint32 col = 0; col < 4; col++)
        {
            real32 sum = 0.0f;
            for (uint32 k = 0; k < 4; k++)
            {
                sum += a.data[col + k * 4] * b.data[k + row * 4];
            }
            res.data[col + row * 4] = sum;
        }
    }

    return res;
}

inline Vec3 operator*(Matrix4x4 &a, Vec3 &b)
{
    Vec3 res = {};

    res.x = a.rows[0].x * b.x + a.rows[0].y * b.y + a.rows[0].z * b.z;
    res.y = a.rows[1].x * b.x + a.rows[1].y * b.y + a.rows[1].z * b.z;
    res.z = a.rows[2].x * b.x + a.rows[2].y * b.y + a.rows[2].z * b.z;
    
    return res;
}


inline Vec4 operator*(Matrix4x4 &a, Vec4 &b)
{
    Vec4 res = {};

    res.x = a.rows[0].x * b.x + a.rows[0].y * b.y + a.rows[0].z * b.z + a.rows[0].w * b.w;
    res.y = a.rows[1].x * b.x + a.rows[1].y * b.y + a.rows[1].z * b.z + a.rows[1].w * b.w;
    res.z = a.rows[2].x * b.x + a.rows[2].y * b.y + a.rows[2].z * b.z + a.rows[2].w * b.w;
    res.z = a.rows[3].x * b.x + a.rows[3].y * b.y + a.rows[3].z * b.z + a.rows[3].w * b.w;
    
    return res;
}

inline 
void translateMat(Matrix4x4 &mat, const Vec3 &translation)
{
    mat.data[3] = translation.x;
    mat.data[3 + 1 * 4] = translation.y;
    mat.data[3 + 2 * 4] = translation.z;
}

inline 
void scaleMat(Matrix4x4 &mat, const Vec3 &scale)
{
    mat.data[0 + 0 * 4] = scale.x;
    mat.data[1 + 1 * 4] = scale.y;
    mat.data[2 + 2 * 4] = scale.z;
}

inline 
void rotateMat(Matrix4x4 &mat, const Vec3 &axis, const real32 angle)
{

}

inline Matrix4x4 inverseMat(Matrix4x4 &mat)
{
    Matrix4x4 res = createMat4x4();

    res.data[0] = mat.data[5] * mat.data[10] * mat.data[15] -
                  mat.data[5] * mat.data[11] * mat.data[14] -
                  mat.data[9] * mat.data[6] * mat.data[15] +
                  mat.data[9] * mat.data[7] * mat.data[14] +
                  mat.data[13] * mat.data[6] * mat.data[11] -
                  mat.data[13] * mat.data[7] * mat.data[10];

    res.data[4] = -mat.data[4] * mat.data[10] * mat.data[15] +
                   mat.data[4] * mat.data[11] * mat.data[14] +
                   mat.data[8] * mat.data[6] * mat.data[15] -
                   mat.data[8] * mat.data[7] * mat.data[14] -
                   mat.data[12] * mat.data[6] * mat.data[11] +
                   mat.data[12] * mat.data[7] * mat.data[10];

    res.data[8] = mat.data[4] * mat.data[9] * mat.data[15] -
                  mat.data[4] * mat.data[11] * mat.data[13] -
                  mat.data[8] * mat.data[5] * mat.data[15] +
                  mat.data[8] * mat.data[7] * mat.data[13] +
                  mat.data[12] * mat.data[5] * mat.data[11] -
                  mat.data[12] * mat.data[7] * mat.data[9];

    res.data[12] = -mat.data[4] * mat.data[9] * mat.data[14] +
                    mat.data[4] * mat.data[10] * mat.data[13] +
                    mat.data[8] * mat.data[5] * mat.data[14] -
                    mat.data[8] * mat.data[6] * mat.data[13] -
                    mat.data[12] * mat.data[5] * mat.data[10] +
                    mat.data[12] * mat.data[6] * mat.data[9];

    res.data[1] = -mat.data[1] * mat.data[10] * mat.data[15] +
                  mat.data[1] * mat.data[11] * mat.data[14] +
                  mat.data[9] * mat.data[2] * mat.data[15] -
                  mat.data[9] * mat.data[3] * mat.data[14] -
                  mat.data[13] * mat.data[2] * mat.data[11] +
                  mat.data[13] * mat.data[3] * mat.data[10];

    res.data[5] = mat.data[0] * mat.data[10] * mat.data[15] -
                  mat.data[0] * mat.data[11] * mat.data[14] -
                  mat.data[8] * mat.data[2] * mat.data[15] +
                  mat.data[8] * mat.data[3] * mat.data[14] +
                  mat.data[12] * mat.data[2] * mat.data[11] -
                  mat.data[12] * mat.data[3] * mat.data[10];

    res.data[9] = -mat.data[0] * mat.data[9] * mat.data[15] +
                   mat.data[0] * mat.data[11] * mat.data[13] +
                   mat.data[8] * mat.data[1] * mat.data[15] -
                   mat.data[8] * mat.data[3] * mat.data[13] -
                   mat.data[12] * mat.data[1] * mat.data[11] +
                   mat.data[12] * mat.data[3] * mat.data[9];

    res.data[13] = mat.data[0] * mat.data[9] * mat.data[14] -
                   mat.data[0] * mat.data[10] * mat.data[13] -
                   mat.data[8] * mat.data[1] * mat.data[14] +
                   mat.data[8] * mat.data[2] * mat.data[13] +
                   mat.data[12] * mat.data[1] * mat.data[10] -
                   mat.data[12] * mat.data[2] * mat.data[9];

    res.data[2] = mat.data[1] * mat.data[6] * mat.data[15] -
                  mat.data[1] * mat.data[7] * mat.data[14] -
                  mat.data[5] * mat.data[2] * mat.data[15] +
                  mat.data[5] * mat.data[3] * mat.data[14] +
                  mat.data[13] * mat.data[2] * mat.data[7] -
                  mat.data[13] * mat.data[3] * mat.data[6];

    res.data[6] = -mat.data[0] * mat.data[6] * mat.data[15] +
                  mat.data[0] * mat.data[7] * mat.data[14] +
                  mat.data[4] * mat.data[2] * mat.data[15] -
                  mat.data[4] * mat.data[3] * mat.data[14] -
                  mat.data[12] * mat.data[2] * mat.data[7] +
                  mat.data[12] * mat.data[3] * mat.data[6];

    res.data[10] = mat.data[0] * mat.data[5] * mat.data[15] -
                   mat.data[0] * mat.data[7] * mat.data[13] -
                   mat.data[4] * mat.data[1] * mat.data[15] +
                   mat.data[4] * mat.data[3] * mat.data[13] +
                   mat.data[12] * mat.data[1] * mat.data[7] -
                   mat.data[12] * mat.data[3] * mat.data[5];

    res.data[14] = -mat.data[0] * mat.data[5] * mat.data[14] +
                    mat.data[0] * mat.data[6] * mat.data[13] +
                    mat.data[4] * mat.data[1] * mat.data[14] -
                    mat.data[4] * mat.data[2] * mat.data[13] -
                    mat.data[12] * mat.data[1] * mat.data[6] +
                    mat.data[12] * mat.data[2] * mat.data[5];

    res.data[3] = -mat.data[1] * mat.data[6] * mat.data[11] +
                    mat.data[1] * mat.data[7] * mat.data[10] +
                    mat.data[5] * mat.data[2] * mat.data[11] -
                    mat.data[5] * mat.data[3] * mat.data[10] -
                    mat.data[9] * mat.data[2] * mat.data[7] +
                    mat.data[9] * mat.data[3] * mat.data[6];

    res.data[7] = mat.data[0] * mat.data[6] * mat.data[11] -
                    mat.data[0] * mat.data[7] * mat.data[10] -
                    mat.data[4] * mat.data[2] * mat.data[11] +
                    mat.data[4] * mat.data[3] * mat.data[10] +
                    mat.data[8] * mat.data[2] * mat.data[7] -
                    mat.data[8] * mat.data[3] * mat.data[6];

    res.data[11] = -mat.data[0] * mat.data[5] * mat.data[11] +
                    mat.data[0] * mat.data[7] * mat.data[9] +
                    mat.data[4] * mat.data[1] * mat.data[11] -
                    mat.data[4] * mat.data[3] * mat.data[9] -
                    mat.data[8] * mat.data[1] * mat.data[7] +
                    mat.data[8] * mat.data[3] * mat.data[5];

    res.data[15] = mat.data[0] * mat.data[5] * mat.data[10] -
                    mat.data[0] * mat.data[6] * mat.data[9] -
                    mat.data[4] * mat.data[1] * mat.data[10] +
                    mat.data[4] * mat.data[2] * mat.data[9] +
                    mat.data[8] * mat.data[1] * mat.data[6] -
                    mat.data[8] * mat.data[2] * mat.data[5];

    real32 determinant = mat.data[0] * res.data[0] + mat.data[1] * res.data[4] + mat.data[2] * res.data[8] + mat.data[3] * res.data[12];
    determinant = 1.0f / determinant;

    for (uint32 i = 0; i < 16; i++)
    {
        mat.data[i] = res.data[i] * determinant;
    }

    return res;
}

inline void invertMat(Matrix4x4 &mat)
{
   
}

inline 
Matrix4x4 orthoMat(real32 left, real32 right, real32 top, real32 bottom, real32 near, real32 far)
{
    Matrix4x4 res = createMat4x4();

    res.data[0 + 0 * 4] = 2.0f / (right - left);
    res.data[1 + 1 * 4] = 2.0f / (top - bottom);
    res.data[2 + 2 * 4] = 2.0f / (near - far);

    res.data[0 + 3 * 4] = (left + right) / (left - right);
    res.data[1 + 3 * 4] = (bottom + top) / (bottom - top);
    res.data[2 + 3 * 4] = (far + near) / (far - near);

    return res;
}

inline
Matrix4x4 perspectiveMat(real32 fov, real32 ar, real32 n, real32 f)
{
    Matrix4x4 res = createMat4x4();

    real32 radians = DegreesToRadians(fov * 0.5f);

    real32 q = 1.0f / tanf(radians);
    real32 a = q / ar;
    
    real32 b = (n + f) / (n - f);
    real32 c = (2.0f * n * f) / (n - f);

    res.data[0 + 0 * 4] = a;
    res.data[1 + 1 * 4] = q;
    res.data[2 + 2 * 4] = b;
    res.data[2 + 3 * 4] = -1.0f;
    res.data[3 + 2 * 4] = c;
    
    return res;
}

inline Matrix4x4 lookAt(const Vec3 &pos, const Vec3 &forward, const Vec3 &up)
{
    Matrix4x4 res = createMat4x4();

    Vec3 s = CrossProduct(forward, Normalize(up));
    Vec3 r = CrossProduct(s, forward);

    res.data[0 + 0 * 4] = s.x;
    res.data[0 + 1 * 4] = s.y;
    res.data[0 + 2 * 4] = s.z;

    res.data[1 + 0 * 4] = r.x;
    res.data[1 + 1 * 4] = r.y;
    res.data[1 + 2 * 4] = r.z;

    res.data[2 + 0 * 4] = -forward.x;
    res.data[2 + 1 * 4] = -forward.y;
    res.data[2 + 2 * 4] = -forward.z;

    Vec3 translation = createVec3(-pos.x, -pos.y, -pos.z);

    Matrix4x4 translationMatrix = createMat4x4();

    translateMat(translationMatrix, translation);

    res = res * translationMatrix;

    return res;
}

inline 
Matrix4x4 transposeMat(Matrix4x4 &mat)
{    
    return createMat4x4(createVec4(mat.rows[0].x, mat.rows[1].x, mat.rows[2].x, mat.rows[3].x),
        createVec4(mat.rows[0].y, mat.rows[1].y, mat.rows[2].y, mat.rows[3].y),
        createVec4(mat.rows[0].z, mat.rows[1].z, mat.rows[2].z, mat.rows[3].z),
        createVec4(mat.rows[0].w, mat.rows[1].w, mat.rows[2].w, mat.rows[3].w));
}

inline Matrix4x4 toMat4(const Quaternion &quat)
{
    Vec3 r = quat * createVec3(1, 0, 0);
    Vec3 u = quat * createVec3(0, 1, 0);
    Vec3 f = quat * createVec3(0, 0, 1);

    return createMat4x4(r.x, r.y, r.z, 0,
        u.x, u.y, u.z, 0,
        f.x, f.y, f.z, 0,
        0, 0, 0, 1
    );
}

struct AABB
{
    Vec3 min, max;
};

inline 
AABB createAABB(Vec3 min, Vec3 max)
{
    AABB res = {};

    res.min = min;
    res.max = max;

    return res;
}

#endif // !MATH_CPP

