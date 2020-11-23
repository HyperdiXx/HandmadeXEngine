
std::atomic<uint32> counter{ 0 };
std::mutex lock_mtx;
std::condition_variable cnd_var;
std::vector<std::thread> threadsPool;
RingQueue<Task, 64> tasksQueue;

bool32 ThreadPool::init()
{
    const auto maxThreads = std::thread::hardware_concurrency();

    //auto numThreads = std::max(1u, maxThreads - 1);

    for (uint32_t i = 0; i < maxThreads - 1; ++i)
    {
        std::thread task_executor([]
        {
            while (true)
            {
                //if (!taskExecution())
                //{
                    std::unique_lock<std::mutex> lock(lock_mtx);
                    cnd_var.wait(lock);
                //}
            }
        });

        task_executor.detach();
    }

    return true;
}

bool32 ThreadPool::taskExecution()
{ 
    Task functionTask;
    
    if (tasksQueue.pop_front(functionTask))
    {
        functionTask();
        counter.fetch_sub(1);

        return true;
    }

    return false;
}

void ThreadPool::addTask(const Task &task)
{
    counter.fetch_add(1);
    
    while (!tasksQueue.push_back(task))
    {
        cnd_var.notify_all();
    }

    cnd_var.notify_one();
}

void ThreadPool::wait()
{
    cnd_var.notify_all();

    while (isWorking())
    {
        taskExecution();
    }
}
bool32 ThreadPool::isWorking()
{
    return counter.load() > 0;    
}