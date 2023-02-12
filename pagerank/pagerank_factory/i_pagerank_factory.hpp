#pragma once

namespace srng{

class IPagerankFactory
{
public:
    virtual ~IPagerankFactory() = default;
    virtual void update() const = 0;
};

}//namespace srng
