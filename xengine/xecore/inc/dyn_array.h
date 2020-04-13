#pragma once

#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include "types.h"
#include "memory_allocate.h"
#include "assert.h"

template<typename T>
class xedyn_array
{
public:

    // TODO : refactor init of capacity and memory block at push_back 
    xedyn_array() 
    {
        m_capacity = 8;
        m_cur_size = 0;
        m_data = (T*)allocate_memory(sizeof(T) * m_capacity);
    }

    xedyn_array(xedyn_array &&rhs)
    {
        m_capacity = 0;
        m_cur_size = 0;
        m_data = nullptr;
        swap(rhs);
    }
    
    ~xedyn_array()
    {
        destroy_data(m_data, m_data + m_cur_size);
        deallocate_memory(m_data);
        m_data = nullptr;
    }

    void push_back(T d)
    {
        assert(m_data);
        if (m_cur_size >= m_capacity)
            resize();

        m_data[m_cur_size] = d;
        ++m_cur_size;
    }

    void insert(uint32 index, const T &d)
    {
        if (m_cur_size >= m_capacity)
            resize();
        memmove(m_data + index + 1, m_data + index, sizeof(T) * (m_cur_size - index));
        m_data[index] = d;
        ++m_cur_size;
    }

    void pop()
    {
        assert(m_cur_size > 0);
        m_data[m_cur_size - 1].~T();
        --m_cur_size;     
    }

    void pop_first()
    {
        assert(m_cur_size > 0);
    }

    void remove(const T &d)
    {
        for (uint32 i = 0; i < m_cur_size; i++)
        {
            if (m_data[i] == d)
            {
                remove(i);
                return;
            }
        }
    }

    void remove(uint32 index)
    {
        if(index > 0 && index < m_cur_size - 1)
        {
            m_data[index].~T();
            memcpy(m_data + index, m_data + index + 1, sizeof(T) * (m_cur_size - index - 1));
            --m_cur_size;
        }
    }

    void emplace(uint32 index, const T &d)
    {
        
    }

    void swap(xedyn_array<T> &rhs)
    {
        uint32 tmp = rhs.m_capacity;
        rhs.m_capacity = m_capacity;
        m_capacity = tmp;

        tmp = m_cur_size;
        m_cur_size = rhs.m_cur_size;
        rhs.m_cur_size = tmp;

        T* t = rhs.m_data;
        rhs.m_data = m_data;
        m_data = t;

    }

    void reserve(uint32 scale)
    {
        m_capacity = m_capacity << scale;
        m_data = (T*)realloc_memory(m_data, sizeof(T) * m_capacity);
    }
    
    void clear()
    {
        assert(m_data);
        
        destroy_data(m_data, m_data + m_cur_size);
        deallocate_memory(m_data);
        
        m_data = nullptr;
        m_capacity = 0;
        m_cur_size = 0;
    }

    bool32 empty() const
    {
        return m_cur_size == 0;
    }

    T* first() const 
    { 
        return m_data; 
    }

    T* last() const 
    { 
        return m_data ? m_data + m_cur_size : nullptr; 
    }

    T& operator[](uint32 i)
    {
        assert(i >= 0 && i <= m_cur_size - 1);
        return m_data[i];
    }

    const T& operator[](uint32 i) const
    {
        assert(i >= 0 && i <= m_cur_size - 1);
        return m_data[i];
    }
    
    inline uint32 get_capacity() const
    {
        return m_capacity;
    }

    inline uint32 size() const
    {
        return m_cur_size;
    }

    inline uint32 size_in_bytes() const
    {
        return sizeof(T) * m_cur_size;
    }
       
private:
    void resize()
    {
        m_capacity = m_capacity << 1;
        m_data = (T*)realloc_memory(m_data, sizeof(T) * m_capacity);       
    }

    void destroy_data(T *first, T* last)
    {
        for(T* i = first; i < last; ++i)
        {
            i->~T();
        }
    }

private:
    T *m_data;
    uint32 m_capacity;
    uint32 m_cur_size;
};
#endif // !DEYN_ARRAY_H

