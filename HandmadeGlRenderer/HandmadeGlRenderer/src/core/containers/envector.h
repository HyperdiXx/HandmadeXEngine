#pragma once

#include "src/application/xenpch.h"


template<typename T>
class Myvector
{
private:
    T *first;
    size_t n;
    size_t capacity;
public:

    vector()
    {
        capacity = 10;
        this->n = 0;
        first = (T*)malloc(sizeof(T) * capacity);
    }

    vector(unsigned int s)
    {
        capacity = 10;
        this->n = s;
        first = (T*)malloc(sizeof(T) * capacity);
    }
    
    vector(const vector<T>& v)
    {
        this->capacity = v.capacity;
        this->size = v.n;
        this->first = v.first;

        std::copy(v.first, v.first + v.n, first);
    }
    vector(vector<T> && v)
    {
        capacity = 0;
        n = 0;
        first = nullptr;
        swap(v);
    }

    ~vector()
    {
        this->capacity = 0;
        this->n = 0;
        free(first);
    }

    vector<T>& operator=(vector<T> const& v)
    {
        free(first);
        first = nullptr;
        this->capacity = v.capacity;
        this->n = v.n;
        first = (T*)malloc(sizeof(T) * capacity);
        std::copy(v.first, v.first + n, first);
        return *this;
    }
    vector<T>& operator=(vector<T> && v)
    {
        free(first);
        this->capacity = 0;
        this->n = 0;
        first = nullptr;
        swap(v);
        return *this;
    }

    void resize(size_t cap)
    {
        if (cap <= capacity)
            return;

        T* newf = (T *)malloc(sizeof(T) * cap);

        for (int i = 0; i < capacity; ++i)
        {
            newf[i] = first[i];
        }
        capacity = cap;
        free(first);
        first = newf;
    }

    void push_back(T d)
    {
        if (n == capacity)
                resize(capacity << 1);
        first[n] = d;
        ++n;
    }

    void insert(int pos, T d)
    {
        push_back(0);

        for (size_t el = n - 1; el > pos; --el)
        {
           first[el] = first[el - 1];
        }

        first[pos] = d;
    }

    void pop()
    {
        for (size_t i = 0; i < n; ++i)
        {
            first[i] = first[i + 1];
        }
       --n;
    }

    bool empty()
    {
        if (first[0] == 0)
            return true;
        return false;
    }

    void pop_back()
    {
        if (first[0] != 0)
            --n;
        for (size_t i = 1; i < n; ++i)
        {
            first[i + 1] = first[i];
        }
    }

   
    void erase(const int pos)
    {
        first[pos] = 0;
    }

    T at(const int i) const
    {
        if (i > n)
            return 0;
        return first[i];
    }

    T& front() const
    {
        if (n > 0)
            return first[0];
    }

    T& back() const
    {
        return first[n - 1];
    }

    size_t begin() const
    {
        if (n > 0)
            return 0;
        else
            std::cout << "Vector is empty!\n";
    }

    size_t end() const
    {
        if(n != 0)
            return n - 1;
        else
            std::cout << "Vector is empty!\n";
    }

    int emplace(const int pos, const int d)
    {
        first[pos] = d;
    }

    size_t max_size() const
    {
        return capacity;
    }

    size_t size() const
    {
        return n;
    }

    T get(int ind)
    {
        return first(ind);
    }

    void set(int ind, T d)
    {
        if (ind < 0 || ind > n)
            return;

        first[ind] = d;
    }

    void swap(vector & other)
    {
        T* tmparray = first;
        size_t tmpcount = n;
        size_t tmpcapacity = capacity;

        first = other.first;
        n = other.n;
        capacity = other.capacity;

        other.first = tmparray;
        other.n = tmpcount;
        other.capacity = tmpcapacity;
    }

    T& operator[](T i)
    {
        return first[i];
    }

    const T& operator[](T i) const
    {
        return first[i];
    }

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        os << v.at(i) << " ";
    }
   
    return os;
}


