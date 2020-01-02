#pragma once

#ifndef STACKLALLOCATOR_H
#define STACKLALLOCATOR_H

#include "types.h"
#include "memory_allocate.h"

class StackAllocator
{
public:
    StackAllocator(uint32 size)
    {
        allocate_block(size);
    }

    ~StackAllocator() {}

    void allocate_block(uint32 size)
    {
        m_cur_pos = allocate_memory(size);
        m_offset = 0;
    }

    void* get_memory_block(uint32 size, uint32 alignment)
    {
        uint32 cur_block = (uint32)m_cur_pos + m_offset;

        uint32 multiplier = (cur_block / alignment) + 1;
        uint32 aligned_address = multiplier * alignment;
        uint32 padding = aligned_address - cur_block;

        m_offset += padding;

        uint32 next_block = cur_block + padding;
        uint32 byte_padding = next_block - sizeof(char);

        char padbyte = padding;

        char *head = (char*)byte_padding;
        head = &padbyte;

        m_offset += size;

        m_used_block = m_offset;

        return (void*)next_block;
    }


    void free(void *ptr)
    {

    }

    void clear()
    {
        deallocate_memory(m_cur_pos);
        m_cur_pos = nullptr;
        m_offset = 0;
        m_used_block = 0;
    }
    
private:
    uint32 m_used_block = 0;
    uint32 m_offset = 0;
    void *m_cur_pos = nullptr;
};
#endif // !STACKLALLOCATOR_H

