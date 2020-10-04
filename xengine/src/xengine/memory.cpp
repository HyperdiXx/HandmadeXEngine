
internal MemoryArena createMemoryArena(void *begin, uint64 size)
{
    MemoryArena arena = {};

    if (!arena.start)
    {
        arena.start = platform_state->AllocateMemory(begin, size);
    }

    arena.curr_index = (char*)arena.start;
    arena.size = size;
    arena.curr_size = 0;

    return arena;
}

internal void* allocateMemory(MemoryArena *arena, uint64 new_size)
{
    if (!arena)
    {
        return nullptr;
    }

    void *memory_location = arena->curr_index;
    arena->curr_index += new_size;
    arena->curr_size  += new_size;

    return memory_location;
}

internal void deallocateMemory(MemoryArena *arena, void *ptr)
{
    //
}
