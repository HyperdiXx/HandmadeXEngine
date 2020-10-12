
#ifndef MEMORY_H
#define MEMORY_H

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

struct MemoryArena
{
    char *curr_index;
    void *start;
    uint64 curr_size, size;
};
#endif
