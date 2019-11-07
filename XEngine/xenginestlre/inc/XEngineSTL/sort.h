#pragma once


#ifndef SORT_H
#define SORT_H

#include "types.h"

namespace xenginestl
{
    void swap(int *a, int *b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }


    void bublesort(int* arr, uint32 n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }


    void selectionsort(int* arr, uint32 n)
    {

    }
}
#endif // !SORT_H

