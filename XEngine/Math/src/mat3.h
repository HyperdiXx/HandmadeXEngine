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
         * Row-major notation matrix 3x3 real32 val
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

        //Creates identity matrix
        mat3(real32 iden)
        {
            for (size_t i = 0; i < ELEMENT_COUNT; i++)
                elem[i] = 0.0f;

            elem[0 + 0 * ROW_COUNT] = iden;
            elem[1 + 1 * ROW_COUNT] = iden;
            elem[2 + 2 * ROW_COUNT] = iden;
        }

        mat3(real32 m00, real32 m01, real32 m02,
             real32 m10, real32 m11, real32 m12, 
             real32 m20, real32 m21, real32 m22)
        {
            elem[0] = m00;
            elem[1] = m01;
            elem[2] = m02;

            elem[3] = m10;
            elem[4] = m11;
            elem[5] = m12;

            elem[6] = m20;
            elem[7] = m21;
            elem[8] = m22;
        }

        inline void transpose() const;
        mat3 getTransposed();

        inline vec3 getDiagonal() const;
        inline vec3 getTranslation() const;

        inline vec3 getRow(int32 num) const;
        inline void setRow(int32 num, vec3* data);

        void printElements() const
        {
            printf("\nMatrix 3x3\n");
            for (size_t i = 0; i < ELEMENT_COUNT; i = i + 3)
            {
                printf("%f %f %f\n", elem[i], elem[i + 1], elem[i + 2]);
            }
            printf("\n");
        }
       
    };
}
#endif