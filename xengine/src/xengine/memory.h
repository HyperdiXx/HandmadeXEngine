
#ifndef MEMORY_H
#define MEMORY_H

struct MemoryArena
{
    char *curr_index;
    void *start;
    uint64 curr_size, size;
};


#endif
