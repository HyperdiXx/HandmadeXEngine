#include "mat3.h"


void mat3::transpose() const
{
}

mat3 mat3::getTransposed()
{
    mat3 res;
    res.transpose();
    return res;
}

vec3f mat3::getDiagonal() const
{
    vec3f res;
    res.set(elem[0 + 0 * ROW_COUNT], elem[1 + 1 * ROW_COUNT], elem[2 + 2 * ROW_COUNT]);
    return res;
}

vec3f mat3::getTranslation() const
{
    vec3f res;

    return res;
}

vec3f mat3::getRow(int32 num) const
{
    vec3f res;
    if (num < 0 || num > ELEMENT_COUNT - 1)
        return vec3f(0.0f, 0.0f, 0.0f);

    res.set(elem[num * ROW_COUNT], elem[num * ROW_COUNT + 1], elem[num * ROW_COUNT + 2]);

    return res;
}

void mat3::setRow(int32 num, vec3f *data)
{
    if (num < 0 || num > ELEMENT_COUNT - 1)
        return;
    elem[num * ROW_COUNT] = data->x;
    elem[num * ROW_COUNT + 1] = data->y;
    elem[num * ROW_COUNT + 2] = data->z;
}
