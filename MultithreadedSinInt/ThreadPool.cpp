#include "ThreadPool.h"
#include <mutex>
#include <iostream>

using std::move;
using std::mutex;
using std::ref;

void WorkerThread(pFunc func, queue<pair<double, double&>> &params, bool &stop)
{
    static mutex Mutex;
    while (true)
    {
        Mutex.lock();
        if (params.empty() || stop)  // this should be called only after acquiring mutex!
        {
            Mutex.unlock();
            return;
        }
        auto param = params.front();
        params.pop();

        func(param.first, param.second);
        Mutex.unlock();
    }
}

ThreadPool::ThreadPool(unsigned number) :
    m_threads(number > 0 ? number : 1), m_stop(false)
{
}

ThreadPool::ThreadPool(ThreadPool &&pool) :
    m_threads(move(pool.m_threads)), m_stop(pool.m_stop)
{

}

ThreadPool::~ThreadPool()
{
}

ThreadPool &ThreadPool::operator =(ThreadPool && pool)
{
    m_threads = move(pool.m_threads);
    m_stop = pool.m_stop;
    return *this;
}

void ThreadPool::Run(pFunc func, queue<pair<double, double&>> &params)
{
    m_stop = false;
    for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
        (*it).first = move(thread(WorkerThread, func, ref(params), ref(m_stop)));

    for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        bool locked = it->second.try_lock();
        if (locked)
        {
            if (it->first.joinable())
                it->first.join();
            it->second.unlock();
        }
    }
}

void ThreadPool::Stop()
{
    m_stop = true;
    for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        bool locked = it->second.try_lock();
        if (locked)
        {
            if (it->first.joinable())
                it->first.join();
            it->second.unlock();
        }
    }
}
