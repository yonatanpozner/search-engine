#pragma once

#include <vector>
#include <iostream>
#include <mutex>

#include "i_safe_synchronization.hpp"

namespace srng{

class SafeSynchronization :public ISafeSynchronization
{
public:
    operator bool() override;
    void add_thread_mode() override;
    void update_mode_at(size_t const& thread_index, bool const& mode) override;
    
private:
    std::vector<bool> m_threads;
    mutable std::mutex m_mutex;
};

}//namespace srng