

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
        len = 1;
        capacity = 8;
        data = (char*)allocate_memory(capacity);
        data[0] = 0x00;
    }

    xestring(const char* str)
    {
        uint32 cur_len = length(str);

        if (cur_len != 0)
        {
            len = cur_len;

            if (len < 8)
                capacity = 8;

            if (capacity < len)
                capacity = len + 1;

            data = (char*)allocate_memory(capacity);
            memcpy(data, str, len);
            data[len] = 0x00;
        }
        else
        {
            len = 1;
            capacity = 8;
            data = (char*)allocate_memory(capacity);
            data[0] = 0x00;
        }

    }

    xestring(const xestring& rval)
    {
        data = rval.data;
        len = rval.len;
        capacity = rval.capacity;
    }

    ~xestring()
    {
        deallocate_memory(data);
        data = nullptr;
        len = 0;
        capacity = 0;
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
            memcpy(data, str, len);
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
        if (index >= 0 && index < len - 1)
            return data[index];
        return ' ';
    }

    uint32 index_of(char symbol)
    {
        for (uint32 i = 0; i < len; i++)
        {
            if (data[i] == symbol)
                return i;
        }
        return 0;
    }

    bool32 find(char symbol)
    {
        if (data != nullptr)
        {
            for (uint32 i = 0; i < len; i++)
            {
                if (data[i] == symbol)
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
            for (uint32 i = 0; i < len; i++)
            {
                if (data[i] == str[i])
                {

                }
            }
        }
        return *this;
    }

    xestring &erase(uint32 index)
    {
        if (index > len - 1 || !len)
            return *this;
        memmove(data + index, data + index + 1, len - index);
        len--;
        data[len] = 0x00;
        return *this;
    }

    xestring &substr(uint32 pos, uint32 count)
    {
        if (pos > len - 1 || count == 0)
            return *this;

        if (pos + count > len)
            count = len - pos;

        char *new_str = (char*)allocate_memory(capacity);
        memcpy(new_str, data + pos, count);
        len = count;
        new_str[len] = 0x00;
        deallocate_memory(data);
        data = new_str;
        return *this;
    }

    void assign(const char *str)
    {
        if (data == str)
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
        return data[0];
    }

    bool32 is_empty()
    {
        return len == 0;
    }

    // TODO: write iterator

    char last() const
    {
        if (!len)
            return data[0];
        return data[len - 1];
    }

    void clear_str()
    {
        deallocate_memory(data);
        data = nullptr;
        len = 0;
        capacity = 0;
    }

    xestring& operator=(const xestring &str)
    {
        data = str.data;
        len = str.len;
        capacity = str.capacity;
        return *this;
    }
    
    char operator[](uint32 ind) const
    {
        if (ind >= len)
            throw 1;
        return data[ind];
    }

    char & operator[](uint32 index)
    {
        if (index >= len)
            throw 1;
        return data[index];
    }

    const char *c_str() const
    {
        return data;
    }

    uint32 get_length() const
    {
        return len;
    }

    uint32 get_capactiy() const
    {
        return capacity;
    }

    friend std::ostream& operator<< (std::ostream& os, const xestring& str)
    {
        if (str.len > 0)
        {
            for (uint32 i = 0; i < str.len; i++)
                os << str[i];
        }

        return os;
    }

private:   
    char *data = nullptr;
    uint32 len = 0;
    uint32 capacity = 0;
};


#endif // !STRING_H

