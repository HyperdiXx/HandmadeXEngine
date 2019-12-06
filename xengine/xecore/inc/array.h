#pragma once

#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"

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

    void insert(T d, uint32 pos);
    void push_back(T d);
    void pop();

    T& first();
    T& last();
    
    T& operator[](T i)
    {
        return data[i];
    }

    const T& operator[](T i) const
    {
        return data[i];
    }

    inline uint32 get_capacity() const;
    inline uint32 size() const;
    
private:
    T data[8];
    uint32 capacity;
    uint32 cur_size;     
};


template <class T>
void xearray<T>::push_back(T d)
{
    if (cur_size < capacity)
    {
       data[cur_size] = d;
       cur_size++;
    }
}

template <class T>
void xearray<T>::insert(T d, uint32 pos)
{
    if (cur_size > 0 && pos > 0 && pos < capacity - 1)
    {
        push_back(0);
        for (uint32 last = cur_size - 1; last > pos; --last)
        {
            data[last] = data[last - 1];
        }
        data[pos] = d;
    }
}

template <class T>
void xearray<T>::pop()
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

template <class T>
T& xearray<T>::first()
{
    if(cur_size > 0)
        return data[0];
}

template <class T>
T& xearray<T>::last()
{
    if(cur_size > 0)
        return data[cur_size - 1];
}

template <class T>
uint32 xearray<T>::get_capacity() const
{
    return capacity;
}

template <class T>
uint32 xearray<T>::size() const
{
    return cur_size;
}
#endif // !ARRAY_H

