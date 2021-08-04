#pragma once
#include <mutex>
#include <exception>
#include <condition_variable>

#include <iostream>
#define THREAD_ID(tid) "[Thread #" << tid << "] "

class Semaphore
{
private:
    int _n, _count;
    std::mutex _mtx;
    std::condition_variable _empty, _full;

public:
    Semaphore(int n)
        : _n(n), _count(1), _mtx(), _empty(), _full()
    {
        if (n <= 0)
            throw std::invalid_argument("Invalid value");
        _count = n;
    }

    void get(int tid)
    {
        std::unique_lock<std::mutex> lk(this->_mtx);
        _empty.wait(lk, [this]
                    { return this->_count > 0; });
        --this->_count;
        #ifdef _DEBUG
        std::cout << THREAD_ID(tid) << "Got\n";
        #endif
        _full.notify_one();
    }

    void release(int tid)
    {
        std::unique_lock<std::mutex> lk(this->_mtx);
        _full.wait(lk, [this]
                   { return this->_count < this->_n; });
        ++this->_count;
        #ifdef _DEBUG
        std::cout << THREAD_ID(tid) << "Released\n";
        #endif
        _empty.notify_one();
    }
};