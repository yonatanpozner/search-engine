#pragma once

namespace srng{

template<typename T>
class ISafeQueue
{
public:
    virtual ~ISafeQueue() = default;
    virtual void push(T const&) = 0;
    virtual size_t size() const = 0;
    virtual T pop() = 0;
};

}//namespace srng
