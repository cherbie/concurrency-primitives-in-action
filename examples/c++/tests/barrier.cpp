#include <iostream>
#include <thread>
#include <vector>
#include <barrier>
#include <gtest/gtest.h>

const int NUM_THREADS = 5;
std::barrier barrier(NUM_THREADS);

void doWork(int id)
{
    std::cout << "Thread " << id << " is doing some work before the barrier." << std::endl;

    // All threads will wait here until all threads have reached this point
    barrier.arrive_and_wait();

    // This part of the code will execute only after all threads have reached the barrier
    std::cout << "Thread " << id << " is doing some work after the barrier." << std::endl;
}

TEST(BarrierExample, TestIncrementSharedData)
{
    std::vector<std::thread> thread_handles;

    // Create and start threads
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        thread_handles.emplace_back(doWork, i);
    }

    // Wait for all threads to finish
    for (auto &thread : thread_handles)
    {
        thread.join();
    }
}
