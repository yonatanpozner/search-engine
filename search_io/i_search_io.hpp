#pragma once

namespace srng{

class ISearchIO
{
public:
    virtual ~ISearchIO() = default;
    virtual void get_input_search_send_output() = 0;
};

}//namespace srng
