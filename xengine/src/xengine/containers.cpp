#pragma once

#ifndef CONTAINERS_CPP
#define CONTAINERS_CPP

template <class T> 
inline void swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <class T> struct Graph
{

};

template <class T> struct BinarySearchTree
{
    struct Node
    {
        T data;
        Node *left;
        Node *right;
    };

};

template <class T> struct DynArray
{
    void* (*allocF) (int size);
    void (*freeF) (void *ptr);

    void init(void* (*alloca) (int) = 0, void(*free) (void* ptr) = 0);

    void reserve(uint32 size);

    void push_back(T new_element);
    void push_back(T* new_element);

    void pop();

    void find(T elem);
    void find(T &elem);

    void clear();

    T& operator[] (int index);
    T& at(int index);

    T* begin() { return data; }
    T* end() { return data + count; }

    const uint32 size() const { return count; }

    T* data;
    uint32 count;
    uint32 capacity;
    bool32 allocator;
};

template <class T> DynArray<T> createDynArray(uint32 size = 8, void* (*alloc) (int) = 0, void (*free) (void *ptr) = 0)
{
    DynArray<T> result = {};

    result.init(alloc, free);
    result.reserve(size);

    return result;
};

template <class T> void DynArray<T>::init(void* (*allocFunc) (int) = 0, void (*freeFunc) (void* ptr) = 0)
{
    count = 0;

    if (allocFunc)
    {
        allocator = true;
    }

    this->allocF = allocFunc;
    this->freeF = freeFunc;

    if (!data)
    {
        data = (T*)platform_state->AllocateMemory(0, 8);
    }
}

template <class T> void DynArray<T>::reserve(uint32 size)
{
    capacity = max(size, capacity);
}

template <class T> void DynArray<T>::push_back(T new_element)
{
    if (count == capacity)
    {
        reserve(capacity << 1);
    }

    data[count++] = new_element;
}

template <class T> T& DynArray<T>::operator[](int i) { return data[i]; }
template <class T> T& DynArray<T>::at(int i) { return data[i]; }

template <class T> struct LinkedList
{
    void init(void *(allocF)(int) = 0);

    void push(T value);
    void insert(T value, uint32 index);

    void pop();
    void remove(uint32 index);

    void clear();

    T* next();
    T* prev();

    struct Node
    {
        T data;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *current_node;

    uint32 count;
};

template <class T> struct HashTable
{
    void hash_function(const char* key);
};

#endif // !CONTAINERS_CPP
