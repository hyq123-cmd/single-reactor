#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include "main.h"

class ThreadPool
{
private:
    int _size;
    int _ISstop_thread;
    std::mutex mu;
    //using a vector to store thread pool  
    std::vector<std::thread> thread_pool;
    //the task for each thread is defined here
    void thread_task(void);           

public:
    //using constructor to create thread pool
    ThreadPool(int size) : _size(size), _ISstop_thread(false)
    { 
        for(int i = 0; i < _size; i++)
            thread_pool.emplace_back(&ThreadPool::thread_task, this);
    }

    std::condition_variable cond;
    std::queue<std::function<void()>> task_queue;

    //deconstructor is uesd to recall all of threads
    ~ThreadPool(void);
};


#endif