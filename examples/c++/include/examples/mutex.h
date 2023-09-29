#ifndef _H_MUTEX
#include <mutex>
#include <memory>

namespace ThreadSafe
{
    class SharedData
    {
    private:
        int m_data = 0;
        std::mutex m_lock;

    public:
        void increment()
        {
            // lock the mutex to protect the critical section
            std::lock_guard<std::mutex> guard(m_lock);
            ++m_data; // increment the shared data
        }

        int read()
        {
            std::lock_guard<std::mutex> guard(m_lock);
            return m_data;
        }
    };
} // namespace ThreadSafe

#endif