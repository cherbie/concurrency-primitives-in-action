#include <iostream>
#include <thread>
#include <mutex>
#include <gtest/gtest.h>

std::mutex mtx;     // Mutex to protect access to shared data
int sharedData = 0; // Shared data

const int numThreads = 5;

void incrementData(int id)
{
    for (int i = 0; i < 5; ++i)
    {
        // Lock the mutex to protect the critical section
        std::unique_lock<std::mutex> lock(mtx);

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(id));

        // Increment the shared data
        ++sharedData;
        std::cout << "Thread " << id << " incremented sharedData to " << sharedData << std::endl;

        // Unlock the mutex when done
        lock.unlock();

        // Continue with other work outside the critical section
        std::this_thread::sleep_for(std::chrono::milliseconds(id));
    }
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

// int main() {
//     std::thread threads[numThreads];

//     // Create threads that increment the shared data
//     for (int i = 0; i < numThreads; ++i) {
//         threads[i] = std::thread(incrementData, i);
//     }

//     // Wait for all threads to finish
//     for (int i = 0; i < numThreads; ++i) {
//         threads[i].join();
//     }

//     // Print the final value of the shared data
//     std::cout << "Final sharedData value: " << sharedData << std::endl;

//     return 0;
// }