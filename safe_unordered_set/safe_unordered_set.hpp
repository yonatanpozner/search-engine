#pragma once

#include <unordered_set>
#include <iterator>
#include <mutex>

#include "i_safe_unordered_set.hpp"

namespace srng{

template<typename T>
class SafeUnorderedSet : public ISafeUnorderedSet<T>
{
public:
    std::pair<typename std::unordered_set<T>::iterator, bool> insert(T const&) override;
    std::unordered_set<T> get_set() const override;
    
private:
    std::unordered_set<T> m_unordered_set;
    mutable std::mutex m_mutex;
};

}//namespace srng

#include "safe_unordered_set.inl"
