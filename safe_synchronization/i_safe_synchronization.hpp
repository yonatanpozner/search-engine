#pragma once

#include <iostream>

namespace srng{

class ISafeSynchronization
{
public:
    virtual operator bool() = 0;
    virtual void add_thread_mode() = 0;
    virtual void update_mode_at(size_t const& thread_index, bool const& mode) = 0;
};

}//namespace srng
