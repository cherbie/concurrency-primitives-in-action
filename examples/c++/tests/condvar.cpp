#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <gtest/gtest.h>

namespace
{
    std::mutex mtx;             // mutex to protect shared data
    std::condition_variable cv; // condition variable for synchronization
    std::queue<int> data;       // shared data (queue)

    const int NUM_ITEMS = 5; // number of items to produce

    inline void producer()
    {
        for (int i = 0; i < NUM_ITEMS; ++i)
        {
            // simulate producing an item
            int item = i;
            {
                std::lock_guard<std::mutex> lock(mtx);

                // add the item to the queue
                data.push(item);
                std::cout << "Produced: " << item << std::endl;
            }

            // notify the consumer that new data is available
            cv.notify_one();

            // simulate some work
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    inline void consumer()
    {
        for (int i = 0; i < NUM_ITEMS; ++i)
        {
            int item;
            {
                std::unique_lock<std::mutex> lock(mtx);

                // wait until there's data to consume
                cv.wait(lock, []
                        { return !data.empty(); });

                // get the item from the queue
                item = data.front();
                data.pop();
            }

            // process the item
            std::cout << "Consumed: " << item << std::endl;

            // simulate some work
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
} // namespace ::

TEST(CondvarExample, TestCondvarConsumerProducerChannel)
{
    std::thread producerThread(::producer);
    std::thread consumerThread(::consumer);

    producerThread.join();
    consumerThread.join();
}