#include "ThreadTest.h"

#include <vector>
#include <sstream>
#include <iostream>

#include <atomic>
#include <thread>

static std::atomic_flag lock = ATOMIC_FLAG_INIT;

static std::atomic<bool> value1;
static std::stringstream stream;

static void thread_test1(int iValue)
{
    while (lock.test_and_set());
    stream << "thread#" << iValue << "\n";
    lock.clear();
}

void atomic1_test()
{
    std::vector<std::thread> vecThread;
    for (int iIndex=0; iIndex<2; iIndex++)
    {
        vecThread.push_back(std::thread(thread_test1, iIndex));
    }

    for (int iIndex=0; iIndex<2; iIndex++)
    {
        vecThread[iIndex].join();
    }

    std::cout<<stream.str();
}

static void thread_test2(int iValue)
{
    while (!value1)
    {
        for (int i=0; i<10000; i++);
        if (!lock.test_and_set())
        {
            std::cout << "thread#" << iValue << std::endl;
        }
    }
}

void atomic2_test()
{
    std::vector<std::thread> vecThread;
    for (int iIndex=0; iIndex<2; iIndex++)
    {
        vecThread.push_back(std::thread(thread_test2, iIndex));
    }

    value1 = true;
    for (auto& th : vecThread)
    {
        if (th.joinable())
        {
            th.join();
        }
    }
}
