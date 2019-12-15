

#ifndef STRING_H
#define STRING_H


#include "types.h"
#include "memory_allocate.h"

#include <ostream>
#include <memory.h>

class xestring
{   
public:
    
    xestring() = default;

    xestring(char symbol)
    {
        m_size = 1;
        m_capacity = 8;
        m_data = (char*)allocate_memory(m_capacity);
        m_data[0] = 0x00;
    }

    xestring(const char* str)
    {
        uint32 cur_len = length(str);

        if (cur_len != 0)
        {
            m_size = cur_len;

            if (m_size < 8)
                m_capacity = 8;

            if (m_capacity < m_size)
                m_capacity = m_size + 1;

            m_data = (char*)allocate_memory(m_capacity);
            memcpy(m_data, str, m_size);
            m_data[m_size] = 0x00;
        }
        else
        {
            m_size = 1;
            m_capacity = 8;
            m_data = (char*)allocate_memory(m_capacity);
            m_data[0] = 0x00;
        }

    }

    xestring(const xestring& rval)
    {
        m_size = rval.m_size;
        m_capacity = rval.m_capacity;
        m_data = (char*)allocate_memory(sizeof(char) * m_capacity);
        memcpy(m_data, rval.m_data, m_capacity * sizeof(char));
        m_data[m_size] = 0x00;
    }

    xestring(xestring&& rval)
    {
        m_size = rval.m_size;
        m_capacity = rval.m_capacity;
        m_data = rval.m_data;
        rval.m_data = nullptr;
        rval.m_size = 0;
    }

    ~xestring()
    {
        deallocate_memory(m_data);
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    uint32 length(const char* data)
    {
        const char * str = data;
        while (*str != '\0')
        {
            str++;
        }
        return (uint32)(str - data);
    }

    void set(const char *str)
    {
        if (str != nullptr)
        {
            uint32 len = length(str);
            memcpy(m_data, str, len);
        }
    }

    void append(char symbol)
    {

    }

    void append(const char *str)
    {

    }

    char find_at(uint8 index)
    {
        if (index >= 0 && index < m_size - 1)
            return m_data[index];
        return ' ';
    }

    uint32 index_of(char symbol)
    {
        for (uint32 i = 0; i < m_size; ++i)
        {
            if (m_data[i] == symbol)
                return i;
        }
        return 0;
    }

    bool32 find(char symbol)
    {
        if (m_data != nullptr)
        {
            for (uint32 i = 0; i < m_size; ++i)
            {
                if (m_data[i] == symbol)
                    return true;
            }
        }
        return false;
    }

    xestring &remove(const char* str)
    {
        const char* cur = str;

        if (str != nullptr)
        {
            for (uint32 i = 0; i < m_size; i++)
            {
                if (m_data[i] == str[i])
                {

                }
            }
        }
        return *this;
    }

    xestring &erase(uint32 index)
    {
        if (index > m_size - 1 || !m_size)
            return *this;
        memmove(m_data + index, m_data + index + 1, m_size - index);
        m_data[m_size] = 0x00;
        --m_size;
        return *this;
    }

    // Modifies same object memory place
    xestring &substr(uint32 pos, uint32 count)
    {
        if (pos > m_size - 1 || count == 0)
            return *this;

        if (pos + count > m_size)
            count = m_size - pos;

        char *new_str = (char*)allocate_memory(m_capacity);
        memcpy(new_str, m_data + pos, count);
        m_size = count;
        new_str[m_size] = 0x00;
        deallocate_memory(m_data);
        m_data = new_str;
        return *this;
    }

    // TODO : dnt use it 
    xestring substr_val(uint32 pos, uint32 count)
    {
        xestring res;
        
        if (pos > res.m_size - 1 || count == 0)
            return nullptr;

        if (pos + count > res.m_size)
            count = res.m_size - pos;

        char *new_str = (char*)allocate_memory(res.m_capacity);
        memcpy(new_str, res.m_data + pos, count);
        res.m_size = count;
        new_str[res.m_size] = 0x00;
        deallocate_memory(res.m_data);
        res.m_data = new_str;
        
        return res;
    }
    
    void assign(const char *str)
    {
        if (m_data == str)
            return;

        uint32 size = length(str);
    }

    void allocate(uint32 size)
    {

    }

    void allocate(const char* str)
    {

    }

    void reserve(uint32 length)
    {

    }

    char first() const
    {
        return m_data[0];
    }

    bool32 is_empty()
    {
        return m_size == 0;
    }

    // TODO: write iterator

    char last() const
    {
        if (m_size <= 1)
            return m_data[0];
        return m_data[m_size - 1];
    }

    void clear_str()
    {
        deallocate_memory(m_data);
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    xestring& operator=(const xestring &str)
    {
        m_data = str.m_data;
        m_size = str.m_size;
        m_capacity = str.m_capacity;
        return *this;
    }
    
    char operator[](uint32 ind) const
    {
        if (ind >= m_size)
            throw 1;
        return m_data[ind];
    }

    char & operator[](uint32 index)
    {
        if (index >= m_size)
            throw 1;
        return m_data[index];
    }

    const char *c_str() const
    {
        return m_data;
    }

    const char *data()
    {
        return m_data;
    }

    void decrease_pointer(uint32 pose)
    {
        m_data[pose]++;
    }

    void decrease_length(uint16 s)
    {
        m_size = m_size - s;
    }

    uint32 get_length() const
    {
        return m_size;
    }

    uint32 get_capactiy() const
    {
        return m_capacity;
    }

    friend std::ostream& operator<< (std::ostream& os, const xestring& str)
    {
        if (str.m_size > 0)
        {
            for (uint32 i = 0; i < str.m_size; i++)
                os << str[i];
        }

        return os;
    }

public:
    char *m_data = nullptr;

private:
   
    uint32 m_size = 0;
    uint32 m_capacity = 0;
};


#endif // !STRING_H

