#include <iostream>
#include <thread>
#include <atomic>
#include <gtest/gtest.h>

std::atomic<int> shared_data(0); // Atomic integer for shared data

const int NUM_THREADS = 5;

void increment_shared_atomic(int thread_id)
{
    // atomically increment the shared data
    shared_data.fetch_add(1, std::memory_order_relaxed);

    std::cout << "Thread " << thread_id
              << " incremented shared_data to " << shared_data.load(std::memory_order_relaxed)
              << std::endl;

    // simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(thread_id));
}

TEST(AtomicExample, TestIncrementSharedAtomic)
{
    std::thread thread_handles[NUM_THREADS];

    // Create threads that increment the shared data
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        thread_handles[i] = std::thread(increment_shared_atomic, i);
    }

    // wait for all threads to finish
    for (auto &thread : thread_handles)
    {
        thread.join();
    }

    // print the final value of the shared data
    const auto final_value = shared_data.load(std::memory_order_relaxed);
    std::cout << "Final shared_data value: " << final_value << std::endl;

    EXPECT_EQ(final_value, NUM_THREADS);
}