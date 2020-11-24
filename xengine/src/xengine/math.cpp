
#pragma once

#ifndef MATH_CPP
#define MATH_CPP

#define PI 					3.1415926535897932f	
#define SMALL_NUMBER		1.e-8f
#define DELTA			    0.00001f
#define FEPSILON            std::numeric_limits<real32>::epsilon()
#define DEPSILON            std::numeric_limits<real64>::epsilon() 

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
        result.x = vec.x * invSqr;
        result.y = vec.y * invSqr;
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

    /*real32 lengthSqr = LengthSqr(vec);
    real32 invSqr = FastInverseSqrt(lengthSqr);
    
    if (invSqr > 0)
    {
        result.x = vec.x * invSqr;
        result.y = vec.y * invSqr;
        result.z = vec.z * invSqr;
    }*/

    real32 len = Length(vec);
    result.x = vec.x / len;
    result.y = vec.y / len;
    result.z = vec.z / len;

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

        real32 data[4][4];
    };

    inline real32& operator()(uint32 row, uint32 col)
    {
        return data[col][row];
    }

    inline const real32 operator()(uint32 row, uint32 col) const
    {
        return data[col][row];
    }
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

        real32 data[3][3];
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
    Vec3 scale;
};

inline Matrix4x4 createMat4x4()
{
    Matrix4x4 result = {};

    memset(result.data, 0, 16 * sizeof(real32));
    result.data[0][0] = 1.0f;
    result.data[1][1] = 1.0f;
    result.data[2][2] = 1.0f;
    result.data[3][3] = 1.0f;

    return result;
}

inline Matrix4x4 createMat4x4(real32 m00, real32 m01, real32 m02, real32 m03,
                              real32 m10, real32 m11, real32 m12, real32 m13,
                              real32 m20, real32 m21, real32 m22, real32 m23,
                              real32 m30, real32 m31, real32 m32, real32 m33)
{
    Matrix4x4 res = {};

    memset(res.data, 0, 16 * sizeof(real32));

    res.data[0][0] = m00; res.data[0][1] = m10; res.data[0][2] = m20; res.data[0][3] = m30;
    res.data[1][0] = m01; res.data[1][1] = m11; res.data[1][2] = m21; res.data[1][3] = m31;
    res.data[2][0] = m02; res.data[2][1] = m12; res.data[2][2] = m22; res.data[2][3] = m32;
    res.data[3][0] = m03; res.data[3][1] = m13; res.data[3][2] = m23; res.data[3][3] = m33;

    return res;
}

inline 
void setMat4(Matrix4x4 &res, real32 m00, real32 m01, real32 m02, real32 m03,
                                    real32 m10, real32 m11, real32 m12, real32 m13,
                                    real32 m20, real32 m21, real32 m22, real32 m23,
                                    real32 m30, real32 m31, real32 m32, real32 m33)
{
    res.data[0][0] = m00; res.data[0][1] = m10; res.data[0][2] = m20; res.data[0][3] = m30;
    res.data[1][0] = m01; res.data[1][1] = m11; res.data[1][2] = m21; res.data[1][3] = m31;
    res.data[2][0] = m02; res.data[2][1] = m12; res.data[2][2] = m22; res.data[2][3] = m32;
    res.data[3][0] = m03; res.data[3][1] = m13; res.data[3][2] = m23; res.data[3][3] = m33;
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

inline Matrix3x3 createMat3x3()
{
    Matrix3x3 result = {};

    memset(result.data, 0, 9 * sizeof(real32));
    result.data[0][0] = 1.0f;
    result.data[1][1] = 1.0f;
    result.data[2][2] = 1.0f;

    return result;
}

inline Matrix3x3 createMat3x3(real32 m00, real32 m01, real32 m02, 
                              real32 m10, real32 m11, real32 m12,
                              real32 m20, real32 m21, real32 m22)
{
    Matrix3x3 res = {};

    memset(res.data, 0, 9 * sizeof(real32));

    res.data[0][0] = m00; res.data[0][1] = m10; res.data[0][2] = m20; 
    res.data[1][0] = m01; res.data[1][1] = m11; res.data[1][2] = m21; 
    res.data[2][0] = m02; res.data[2][1] = m12; res.data[2][2] = m22; 

    return res;
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

    for (uint32 row = 0; row < 4; ++row)
    {
        for (uint32 col = 0; col < 4; ++col)
        {
            res(row, col) = a(row, 0) * b(0, col) + a(row, 1) * b(1, col) + a(row, 2) * b(2, col) + a(row, 3) * b(3, col);
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

    res.x += a(0, 0) * b.x + a(0, 1) * b.y + a(0, 2) * b.z + a(0, 3) * b.w;
    res.y += a(1, 0) * b.x + a(1, 1) * b.y + a(1, 2) * b.z + a(1, 3) * b.w;
    res.z += a(2, 0) * b.x + a(2, 1) * b.y + a(2, 2) * b.z + a(2, 3) * b.w;
    res.w += a(3, 0) * b.x + a(3, 1) * b.y + a(3, 2) * b.z + a(3, 3) * b.w;

    return res;
}

inline Matrix4x4 operator/(const Matrix4x4 &a, real32 b)
{
    Matrix4x4 res = createMat4x4();

    for (uint32 row = 0; row < 4; ++row)
    {
        for (uint32 col = 0; col < 4; ++col)
        {
            res(row, col) /= b;
        }
    }

    return res;
}

inline 
void translateMat(Matrix4x4 &mat, const Vec3 &translation)
{
    mat.data[3][0] = translation.x;
    mat.data[3][1] = translation.y;
    mat.data[3][2] = translation.z;
}

inline 
Matrix4x4 translateMat(const Vec3 &translation)
{
    return createMat4x4(1, 0, 0, translation.x,
                        0, 1, 0, translation.y,
                        0, 0, 1, translation.z,
                        0, 0, 0, 1);
}

inline 
void scaleMat(Matrix4x4 &mat, const Vec3 &scale)
{
    mat.data[0][0] = scale.x;
    mat.data[1][1] = scale.y;
    mat.data[2][2] = scale.z;
}

inline
Matrix4x4 scaleMat(const Vec3 &scale)
{
    return createMat4x4(scale.x, 0, 0, 0,
                        0, scale.y, 0, 0,
                        0, 0, scale.z, 0,
                        0, 0, 0, 1);
}

inline 
void rotateMat(Matrix4x4 &rotation, const Vec3 &axis, real32 euler_angle)
{   
    real32 angle = DegreesToRadians(euler_angle);

    real32 cos_value = cos(angle);
    real32 t = 1.0f - cos_value;

    real32 sin_value = sin(angle);
    
    Vec3 ax = Normalize(axis);
    
    rotation(0, 0) = cos_value + ax.x * ax.x * t;
    rotation(1, 1) = cos_value + ax.y * ax.y * t;
    rotation(2, 2) = cos_value + ax.z * ax.z * t;

    real32 tmp1 = ax.x * ax.y * t;
    real32 tmp2 = ax.z * sin_value;
    
    rotation(1, 0) = tmp1 + tmp2;
    rotation(0, 1) = tmp1 - tmp2;

    tmp1 = ax.x * ax.z * t;
    tmp2 = ax.y * sin_value;
    
    rotation(2, 0) = tmp1 - tmp2;
    rotation(0, 2) = tmp1 + tmp2;

    tmp1 = ax.y * ax.z * t;
    tmp2 = ax.x * sin_value;
    
    rotation(2, 1) = tmp1 + tmp2;
    rotation(1, 2) = tmp1 - tmp2;
   
}

// Calculating minor of 3x3 sub matrix
inline real32
minorMat4x4(Matrix4x4 &mat, uint32 r0, uint32 r1, uint32 r2, uint32 c0, uint32 c1, uint32 c2)
{
    real32 res = mat(r0, c0) * (mat(r1, c1) * mat(r2, c2) - mat(r1, c2) * mat(r2, c1)) - 
                 mat(r0, c1) * (mat(r1, c0) * mat(r2, c2) - mat(r1, c2) * mat(r2, c0)) +
                 mat(r0, c2) * (mat(r1, c0) * mat(r2, c1) - mat(r1, c1) * mat(r2, c0));

    return res;
}

inline
Matrix4x4 adjoint(Matrix4x4 &mat)
{
    return Matrix4x4
    {
         minorMat4x4(mat, 1, 2, 3, 1, 2, 3), -minorMat4x4(mat, 0, 2, 3, 1, 2, 3),  minorMat4x4(mat, 0, 1, 3, 1, 2, 3), -minorMat4x4(mat, 0, 1, 2, 1, 2, 3),
        -minorMat4x4(mat, 1, 2, 3, 0, 2, 3),  minorMat4x4(mat, 0, 2, 3, 0, 2, 3), -minorMat4x4(mat, 0, 1, 3, 0, 2, 3),  minorMat4x4(mat, 0, 1, 2, 0, 2, 3),
         minorMat4x4(mat, 1, 2, 3, 0, 1, 3), -minorMat4x4(mat, 0, 2, 3, 0, 1, 3),  minorMat4x4(mat, 0, 1, 3, 0, 1, 3), -minorMat4x4(mat, 0, 1, 2, 0, 1, 3),
        -minorMat4x4(mat, 1, 2, 3, 0, 1, 2),  minorMat4x4(mat, 0, 2, 3, 0, 1, 2), -minorMat4x4(mat, 0, 1, 3, 0, 1, 2),  minorMat4x4(mat, 0, 1, 2, 0, 1, 2)
    };
}

inline 
real32 determinantMat4x4(Matrix4x4 &mat)
{
    real32 res = mat(0, 0) * minorMat4x4(mat, 1, 2, 3, 1, 2, 3) -
                 mat(0, 1) * minorMat4x4(mat, 1, 2, 3, 0, 2, 3) +
                 mat(0, 2) * minorMat4x4(mat, 1, 2, 3, 0, 1, 3) -
                 mat(0, 3) * minorMat4x4(mat, 1, 2, 3, 0, 1, 2);
    
    return res;
}

inline 
void transposeMat4x4(Matrix4x4 &mat)
{
    real32 t = 0.0f;

    for (uint32 row = 0; row < 4; ++row)
    {
        for (uint32 col = row + 1; col < 4; ++col)
        {
            t = mat(row, col);
            mat(row, col) = mat(col, row);
            mat(col, row) = t;
        }
    }
}

inline Matrix4x4 inverseMat(Matrix4x4 &mat)
{
    Matrix4x4 res = createMat4x4();

    real32 deter = determinantMat4x4(mat);

    res = adjoint(mat) / deter;

    return res;
}

inline 
void invertMat(Matrix4x4 &mat)
{
    


}

inline 
Matrix3x3 convertFrom(const Matrix4x4 &mat)
{
    return createMat3x3
               (mat(0, 0), mat(0, 1), mat(0, 2),
                mat(1, 0), mat(1, 1), mat(1, 2),
                mat(2, 0), mat(2, 1), mat(2, 2));
}

inline 
Matrix4x4 orthoMat(real32 left, real32 right, real32 top, real32 bottom, real32 near, real32 far)
{
    real32 a = 2.0f / (right - left);
    real32 b = 2.0f / (top - bottom);
    real32 e = 2.0f / (near - far);

    real32 c = (left + right) / (left - right);
    real32 d = (bottom + top) / (bottom - top);
    real32 f = (far + near) / (far - near);

    Matrix4x4 res = createMat4x4(a, 0, c, 0,
                                 0, b, d, 0,
                                 0, 0, e, f,
                                 0, 0, 1, 0);
                                 
    return res;
}

inline
Matrix4x4 perspectiveRH(real32 fov, real32 ar, real32 near_plane, real32 far_plane)
{
    Matrix4x4 res = createMat4x4();

    real32 radians = DegreesToRadians(fov * 0.5f);
    real32 tanTheta = tanf(radians);

    real32 q = 1.0f / tanTheta;
    real32 f = ar / tanTheta;

    real32 a = q / ar;
    
    real32 b = (near_plane + far_plane) / (near_plane - far_plane);
    real32 c = (2.0f * near_plane * far_plane) / (near_plane - far_plane);

    //res.data[0][0] = q;
    //res.data[1][1] = a;
    //res.data[2][2] = b;
    //res.data[2][3] = -1.0f;
    //res.data[3][2] = c;
    
    res = createMat4x4(q, 0, 0, 0,
                       0, f, 0, 0,
                       0, 0, b, c,
                       0, 0, -1, 0);
   
    return res;
}

inline Matrix4x4 lookAtRH(const Vec3 &pos, const Vec3 &target, const Vec3 &up)
{
    Vec3 zAxis = Normalize(pos - target);
    Vec3 xAxis = Normalize(CrossProduct(up, zAxis));
    Vec3 yAxis = CrossProduct(zAxis, xAxis);
  
    Matrix4x4 res = createMat4x4(xAxis.x, xAxis.y, xAxis.z, -DotProduct(xAxis, pos),
                                 yAxis.x, yAxis.y, yAxis.z, -DotProduct(yAxis, pos),
                                 zAxis.x, zAxis.y, zAxis.z, -DotProduct(zAxis, pos), 
                                 0, 0, 0, 1.0f);
    
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

inline 
bool32 isEqual(const int32 a, const int32 b)
{
    return a == b;
}

inline 
bool32 isEqual(const uint32 a, const uint32 b)
{
    return a == b;
}

inline 
bool32 isEqual(const uint64 a, const uint64 b)
{
    return a == b;
}

inline 
bool32 isEqual(const real32 a, const real32 b)
{
    return fabs(a - b) <= FEPSILON;
}

inline 
bool32 isEqual(const real64 a, const real64 b)
{
    return fabs(a - b) <= DEPSILON;
}

inline 
uint32 colorFromVec4(Vec4 &color)
{
    uint32 res = 0;

    res = 
        (uint32) (color.x * 255.0f)        |
        ((uint32)(color.y * 255.0f) << 8)  |
        ((uint32)(color.z * 255.0f) << 16) |
        ((uint32)(color.w * 255.0f) << 24);

    return res;
}

inline 
Vec4 colorFromInt(uint32 value)
{
#define O_D_255 0.00392156862f

    Vec4 result = createVec4(0.0f, 0.0f, 0.0f, 0.0f);

    result.x = (value >> 24) & 255;
    result.y = (value >> 16) & 255;
    result.z = (value >> 8) & 255;
    result.w = value & 255;

    // Convert to normalize
    //result.x *= O_D_255;
    //result.y *= O_D_255;
    //result.z *= O_D_255;
    //result.w *= O_D_255;

    result.x /= 255.0f;
    result.y /= 255.0f;
    result.z /= 255.0f;
    result.w /= 255.0f;


    return result;
}

#endif // !MATH_CPP

