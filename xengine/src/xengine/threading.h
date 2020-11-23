#ifndef THREADS_H
#define THREADS_H

template<class T, uint32 size>
class RingQueue
{
public:

    inline bool32 push_back(const T& item)
    {
        bool32 result;

        mtx.lock();

        uint32 next = (head + 1) % size;

        if (next != tail)
        {
            data[head] = item;
            head = next;
            result = true;
        }

        mtx.unlock();

        return result;
    }

    inline bool32 pop_front(T& item)
    {
        bool32 result;

        mtx.lock();

        if (tail != head)
        {
            item = data[tail];
            tail = (tail + 1) % size;
            result = true;
        }

        mtx.unlock();

        return result;
    }


private:
    T data[size];
    std::mutex mtx;
    uint32 head;
    uint32 tail;
};

using Task = std::function<void()>;

class ThreadPool
{
public:
    global bool32 init();
    global void addTask(const Task &task);
    global bool32 taskExecution();

    global void wait();
    global bool32 isWorking();
};
#endif