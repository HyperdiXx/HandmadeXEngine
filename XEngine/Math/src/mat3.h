#pragma once

#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"
#include "vec4.h"
#include "utils.h"


namespace Math
{
    struct MATH_API mat3
    {
        static const int32 ELEMENT_COUNT = 9;
        static const int32 ROW_COUNT = 3;

        /**
         * Row-major notation matrix 3x3 float val
         *
         *       [m00, m01, m02,
         *        m10, m11, m12,
         *        m20, m21, m22]
         */ 

        union 
        {
            struct
            {
                real32 m00, m01, m02;
                real32 m10, m11, m12;
                real32 m20, m21, m22;
            };

            real32	elem[9];
        };

        //Default Constructor.
        mat3()
        {
            for (size_t i = 0; i < ELEMENT_COUNT; i++)
                elem[i] = 0.0f;
        }

        mat3(real32 iden)
        {
            for (size_t i = 0; i < ELEMENT_COUNT; i++)
                elem[i] = 0.0f;

            elem[0 + 0 * ROW_COUNT] = iden;
            elem[1 + 1 * ROW_COUNT] = iden;
            elem[2 + 2 * ROW_COUNT] = iden;
        }

        inline void transpose() const;
        mat3 getTransposed();





    };
}
#endif