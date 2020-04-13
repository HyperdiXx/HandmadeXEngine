#pragma once

#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"
#include "assert.h"

template <typename T>
class xearray
{
public:
    
    xearray() : capacity(8), cur_size(0) {}

    xearray(T d, uint32 s) : data(d), capacity(s) {};
    
    xearray(const xearray &arr) = default;
    xearray(xearray &&arr) = default;

    ~xearray()
    {
        capacity = 0;
        cur_size = 0;       
    }

    void insert(uint32 pos, T d)
    {
        if (cur_size > 0 && pos > 0 && pos < capacity - 1)
        {
            if (cur_size == capacity)
            {
                capacity += 8;
            }

            memcpy(data + pos + 1, data + pos, (cur_size - (pos)) * sizeof(d));
            data[pos] = d;
            cur_size++;
        }
    }
    
    void push_back(T d)
    {
        if (cur_size < capacity)
        {
            data[cur_size] = d;
            cur_size++;
        }
    }

    void pop()
    {
        if (cur_size > 0 && cur_size > 0)
        {
            for (uint32 i = 0; i < cur_size; ++i)
            {
                data[i] = data[i + 1];
            }
            --cur_size;
        }
    }

    T& first()
    {
        assert(cur_size > 0);
        return data[0];
    }

    T& last()
    {
        assert(cur_size > 0);
        return data[cur_size - 1];
    }
    
    T& operator[](T i)
    {
        return data[i];
    }

    const T& operator[](T i) const
    {
        return data[i];
    }

    inline uint32 get_capacity() const
    {
        return capacity;
    }

    inline uint32 size() const
    {
        return size;
    }
    
private:
    T data[8];
    uint32 capacity;
    uint32 cur_size;     
};
#endif // !ARRAY_H

