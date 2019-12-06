#pragma once

#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include "types.h"
#include "memory_allocate.h"

template<typename T>
class xedyn_array
{
public:

    xedyn_array()
    {
        capacity = 8;
        cur_pos = 0;
        data = (T*)allocate_memory(sizeof(T) * capacity);
    }

    ~xedyn_array()
    {
        capacity = 0;
        cur_pos = 0;       
        deallocate_memory(data);
        data = nullptr;
    }

    void push_back(T d);
    void pop();

    void pop_first();

    void resize();
    
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
    T *data;
    uint32 capacity;
    uint32 cur_pos;
};

template <class T>
void xedyn_array<T>::resize()
{
    capacity = capacity << 1;

    T* newf = (T *)allocate_memory(sizeof(T) * capacity);

    //memcpy();

    for (int i = 0; i < capacity; ++i)
    {
        newf[i] = data[i];
    }

    deallocate_memory(data);
    data = newf;
}

template <class T>
void xedyn_array<T>::push_back(T d)
{
    if (data)
    {  
        if (cur_pos >= capacity)
            resize();

        data[cur_pos] = d;
        ++cur_pos;
    }
}

template <class T>
uint32 xedyn_array<T>::get_capacity() const
{
    return capacity;
}

template <class T>
uint32 xedyn_array<T>::size() const
{
    return cur_pos;
}


#endif // !DEYN_ARRAY_H

