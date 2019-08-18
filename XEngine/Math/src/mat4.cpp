#include "mat4.h"
#include "math.h"


namespace Math
{

    mat4 mat4::operator*(const mat4& rhs) const 
    {
        mat4 res = mat4::identity();
        for (int i = 0; i < ROW_COUNT; ++i) 
        {
            for (int j = 0; j < ROW_COUNT; ++j)
            {
                for (int k = 0; k < ROW_COUNT; ++k) 
                {
                   // res.row_col[i][j] += row_col[i][k] * rhs.row_col[k][j];
                }
            }
        }
        return res;
    }

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

    mat4 mat4::rotateRes(const vec3 & rotationVec)
    {
        return rotateX(rotationVec.x) * rotateY(rotationVec.y) * rotateZ(rotationVec.z);
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

        return (res);
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

        return (res);
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

        return (res);
    }

    mat4 mat4::transform(const vec3 & matt, const vec3 & matr, const vec3 & mats)
    {
        return translate(matt) * rotateRes(matr) * scale(mats);
    }
    
    bool mat4::isZero() const
    {
        for (int i = 0; i < ELEM_COUNT; ++i) 
        {
            if (elem[i] != 0) 
                return false;
        }

        return true;
    }

    bool mat4::isIdentity() const
    {


        return false;
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

    float mat4::operator[](int i) const
    {
        if(i > 0 || i < ELEM_COUNT - 1)
            return elem[i];
        return 0.0f;
    }

    bool mat4::operator==(const mat4 & r) const
    {
        for (int i = 0; i < ELEM_COUNT; ++i)
        {
            if (elem[i] != r.elem[i])
                return false;
        }

        return true;
    }

    bool mat4::operator!=(const mat4 & r) const
    {
        for (int i = 0; i < ELEM_COUNT; ++i)
        {
            if (elem[i] != r.elem[i])
            {
                return true;
            }
        }
        return false;
    }

    mat4 mat4::operator+(const mat4 & r) const
    {
        mat4 res;

        for (int i = 0; i < ELEM_COUNT; ++i)
        {
            res.elem[i] += r.elem[i];
        }

        return res;
    }

    mat4 & mat4::operator+=(const mat4 & r)
    {
        for (int i = 0; i < ELEM_COUNT; ++i)
            elem[i] += r.elem[i];

        return *this;
    }

    mat4 mat4::operator-(const mat4 & r) const
    {
        mat4 res;

        for (int i = 0; i < ELEM_COUNT; ++i)
        {
            res.elem[i] -= r.elem[i];
        }

        return res;
    }

    mat4 mat4::operator-=(const mat4 & r)
    {
        for (int i = 0; i < ELEM_COUNT; ++i)
        {
            elem[i] -= r.elem[i];
        }
        return *this;
    }


    mat4 mat4::operator*(const float scalar) const
    {
        mat4 res;

        for (int i = 0; i < ELEM_COUNT; i++)
        {
            res.elem[i] = elem[i] * scalar;
        }

        return res;
    }

    mat4 mat4::operator*=(const float scalar)
    {
        for (int i = 0; i < ELEM_COUNT; i++)
        {
            elem[i] *= scalar;
        }

        return *this;
    }

    vec4<float> mat4::operator*(const vec4<float> & r)
    {
        vec4<float> res;

        res.x = elem[0] * r.x + elem[1] * r.y + elem[2] * r.z + elem[3] * r.w;
        res.y = elem[4] * r.x + elem[5] * r.y + elem[6] * r.z + elem[7] * r.w;
        res.z = elem[8] * r.x + elem[9] * r.y + elem[10] * r.z + elem[11] * r.w;
        res.w = elem[12] * r.x + elem[13] * r.y + elem[14] * r.z + elem[15] * r.w;
            
        return res;
    }

    void mat4::set(int i, float val)
    {
        if (i > 0 || i < ELEM_COUNT - 1)
            elem[i] = val;
    }

    void mat4::set(int i, int j, float val)
    {
        int pos = i + j * ROW_COUNT;

        if (pos > 0 || pos < ELEM_COUNT - 1)
            elem[pos] = val;
    }

    float mat4::get(int i) const
    {
        if(i > 0 || i < ELEM_COUNT - 1)
            return elem[i];
    }

    int mat4::getIndex(int val) const 
    {
        for (int i = 0; i < ELEM_COUNT; ++i)
        {
            if (elem[i] == val)
                return i;
        }

        return false;
    }

    mat4 mat4::transpose() const
    {
        mat4 res = {*this};
        
        std::swap(res.elem[1], res.elem[4]);
        std::swap(res.elem[2], res.elem[8]);
        std::swap(res.elem[3], res.elem[12]);
        std::swap(res.elem[6], res.elem[9]);
        std::swap(res.elem[7], res.elem[13]);
        std::swap(res.elem[11], res.elem[14]);

        return res;
    }

    float mat4::get(int i, int j) const
    {
        int pos = i + j * ROW_COUNT;

        if(pos > 0 || pos < ELEM_COUNT - 1)
            return elem[pos];

        return false;
    }

}
