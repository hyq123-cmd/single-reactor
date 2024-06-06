#include "threadpool.h"

void ThreadPool::thread_task(void)
{
    std::function<void()> f;
    while(true)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [this]{return (_ISstop_thread || !task_queue.empty());});
        if(_ISstop_thread && task_queue.empty()) break;
        f = task_queue.front();
        task_queue.pop();
        locker.unlock();
        f();
    }     

}

ThreadPool::~ThreadPool()
{
    _ISstop_thread = true;
    cond.notify_all();
    for(auto& th : thread_pool)  th.join();
    std::cout << "\ndestructor called" << std::endl; 
}
