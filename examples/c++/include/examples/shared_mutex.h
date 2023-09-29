#ifndef _H_SHARED_MUTEX
#include <shared_mutex>
#include <memory>

namespace ThreadSafe
{
    class SharedData
    {
    private:
        int m_data = 0;
        std::shared_mutex m_rwlock;

    public:
        void increment()
        {
            // lock the mutex to protect the critical section
            std::lock_guard<std::shared_mutex> guard(m_rwlock);
            ++m_data; // increment the shared data
        }

        int read()
        {
            std::shared_lock<std::shared_mutex> shared_lock(m_rwlock);
            int value = m_data;
            shared_lock.unlock();
            return value;
        }
    };
} // namespace ThreadSafe

#endif