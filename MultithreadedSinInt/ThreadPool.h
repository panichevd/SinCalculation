#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using std::mutex;
using std::pair;
using std::queue;
using std::thread;
using std::vector;

typedef void (*pFunc)(double, double&);

class ThreadPool
{
private:
    vector<pair<thread, mutex>> m_threads;
    bool m_stop;
public:
    explicit ThreadPool(unsigned number);
    ThreadPool(ThreadPool && pool);
    ~ThreadPool();

    ThreadPool &operator=(ThreadPool &&pool);

    void Run(pFunc func, queue<pair<double, double&>> &params);
    void Stop();

    bool Stopped() const { return m_stop; }
};

#endif // THREADPOOL_H
