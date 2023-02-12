#include "safe_queue.hpp"

namespace srng{

template<typename T>
void SafeQueue<T>::push(T const& variable)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    m_queue.push(variable);
    m_condition.notify_all();
}

template<typename T>
size_t SafeQueue<T>::size() const
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_queue.size();
}


template <typename T>
inline T SafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> locker(m_mutex);
    while(m_queue.size() == 0)
    {
        m_condition.wait(locker);
    }

    T result = m_queue.front();
    m_queue.pop();

    return result;
}

} // namespace srng
