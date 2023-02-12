#pragma once

#include <unordered_set>
#include <iterator>
#include <mutex>

namespace srng{

template<typename T>
class ISafeUnorderedSet
{
public:
    virtual ~ISafeUnorderedSet() = default;
    virtual std::pair<typename std::unordered_set<T>::iterator, bool> insert(T const&) = 0;
    virtual std::unordered_set<T> get_set() const = 0;
};

}//namespace srng
