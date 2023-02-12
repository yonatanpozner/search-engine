
#include "safe_synchronization.hpp"


namespace srng{

SafeSynchronization::operator bool()
{
    bool result = false;
    std::lock_guard<std::mutex> locker(m_mutex);
    for(auto const& thread : m_threads)
    {
        if(thread)
        {
            result = thread;
        }
    }
    return result;
}

void SafeSynchronization::add_thread_mode()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    m_threads.push_back(true);
}

void SafeSynchronization::update_mode_at(size_t const& thread_index, bool const& mode)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(thread_index < m_threads.size())
    {
        m_threads[thread_index] = mode;
    }
    else
    {
        std::cout << "ERROR: in function update_mode_at(), out of range.\n\n";
    }
}

}//namespace srng
