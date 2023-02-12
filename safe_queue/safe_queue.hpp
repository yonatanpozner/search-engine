#pragma once

#include <mutex>
#include <string>
#include <queue>
#include <optional>
#include <condition_variable>

#include "i_safe_queue.hpp"

namespace srng{

template<typename T>
class SafeQueue : public ISafeQueue<T>
{
public:
    void push(T const&) override;
    size_t size() const override;
    T pop() override;

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
};

}//namespace srng

#include "safe_queue.inl"
