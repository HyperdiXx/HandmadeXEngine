
#ifndef MEMORY_H
#define MEMORY_H

#define alloc_mem new
#define free_mem  delete

struct MemoryStats
{
    uint32 sinze_bytes_allocated;
    uint32 allocations_count;
    uint32 current_allocations_count;
};

struct MemoryArena
{
    char *curr_index;
    void *start;
    uint64 curr_size, size;
};
#endif
