
#ifndef MEMORY_H
#define MEMORY_H

#define alloc_mem new
#define free_mem  delete

struct MemoryStats
{
    uint32 sizeInBytesAllocated;
};

global MemoryStats stats = {};

inline void *operator new(size_t size)
{
    stats.sizeInBytesAllocated += size;
    
    
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
