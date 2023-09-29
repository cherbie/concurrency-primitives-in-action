#include <iostream>
#include <thread>
#include <gtest/gtest.h>
#include <examples/shared_mutex.h>

// TODO: make this case more similar to Rust example

TEST(SharedMutexExample, TestIncrementRwLockSharedData)
{
    const int NUM_THREADS = 5;
    std::thread thread_handles[NUM_THREADS];

    auto shared_data = std::make_shared<ThreadSafe::SharedData>();

    for (int id = 0; id < NUM_THREADS; id++)
    {
        thread_handles[id] = std::thread([id, shared_data]()
                                         {
                                            // threadsafe increment
                                            shared_data->increment();

                                            std::cout << "Thread " << id << " incremented sharedData to " << shared_data->read() << std::endl;

                                            // simulate some work
                                            std::this_thread::sleep_for(std::chrono::milliseconds(id)); });
    }

    // wait for all threads to finish
    for (auto &thread_handle : thread_handles)
    {
        thread_handle.join();
    }

    // print the final value of the shared data
    std::cout << "Final sharedData value: " << shared_data->read() << std::endl;

    EXPECT_EQ(shared_data->read(), NUM_THREADS);
}