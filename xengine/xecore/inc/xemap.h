#pragma once

#ifndef XEMAP_H
#define XEMAP_H

#include "types.h"
#include "memory_allocate.h"
#include "assert.h"

template <typename Key, typename Value>
class xemap
{
public:

    xemap() : m_capacity(0), m_size(0), m_keys(nullptr), m_values(nullptr) {};
    ~xemap() { clear(); m_keys = nullptr; m_values = nullptr; };

    void put(const Key &k, const Value &v)
    {
        if (m_capacity == m_size)
            reserve(1);
        
        int index = find_index(k);

        assert(index >= 0);

        if ((index < m_size && m_keys[index] != k) || index == m_size)
        {
            memmove(m_keys + index + 1, m_keys + index, sizeof(Key) * (m_size - index));
            memmove(m_values + index + 1, m_values + index, sizeof(Value) * (m_size - index));
            
            m_keys[index] = k;
            m_values[index] = v;

            ++m_size;
        }       
    }

    void reserve(uint32 scale)
    {
        if (m_capacity < 2)
            m_capacity = 8;
        else
            m_capacity = m_capacity << scale;
        
        uint32 *new_data = (uint32*)allocate_memory(m_capacity * (sizeof(Key) + sizeof(Value)));

        memcpy(new_data, m_keys, sizeof(Key) * m_size);
        memcpy(new_data + sizeof(Key) * m_capacity, m_values, sizeof(Value) * m_size);

        deallocate_memory(m_keys);
        m_keys = (Key*)new_data;
        m_values = (Value*)(new_data + sizeof(Key) * m_capacity);
    }

    Value& get(const Key& key)
    {
        int ind = find_index(key);
        assert(ind >= 0);
        return m_values[ind];
    }

    const Value& get(const Key& key) const
    {
        int ind = find(key);
        assert(ind >= 0);
        return m_values[ind];
    }

    Value* begin()
    {
        return m_values;
    }

    Value* end()
    {
        return m_values + m_size;
    }

    void clear()
    { 
        assert(m_keys != nullptr);
        assert(m_values != nullptr);
        destroy_data(m_keys);
        destroy_data(m_values);
    }

private:
    int find_index(const Key &key) const
    {
        // binary search
        int first_el = 0;
        int last_el = m_size - 1;

        while (first_el < last_el)
        {
            int middle = (first_el + last_el) >> 1;
            if (m_keys[middle] < key)
                first_el = middle + 1;
            else
                last_el = middle;  
        }

        if (first_el + 1 == m_size && m_keys[first_el] < key)
        {
            return first_el + 1;
        }

        return first_el;
    }

    template <typename T>
    void destroy_data(T *val)
    {
        for (uint32 i = 0; i < m_size; ++i)
        {
            val[i].~T();
        }
    }

private:
    Key *m_keys;
    Value *m_values;
    uint32 m_capacity;
    uint32 m_size;
};
#endif // XMAP_H

