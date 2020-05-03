#pragma once

#include <malloc.h>

#define alloc_mem new
#define free_mem  delete

inline void *operator new(size_t size)
{
    return malloc(size);
}

inline void operator delete(void* block)
{
    free(block);
}