#pragma once

#include <stdlib.h>

inline void* allocate_memory(size_t size)
{
    return malloc(size);
}

inline void* realloc_memory(void* mem, size_t size)
{
    return realloc(mem, size);
}

inline void deallocate_memory(void *mem)
{
    if (mem != nullptr)
        free(mem);
}