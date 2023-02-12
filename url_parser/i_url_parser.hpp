#pragma once

#include <vector>
#include <string>

namespace srng{

class IUrlParser
{
public:
    virtual ~IUrlParser() = default;
    virtual void parse(std::string, std::vector<std::string>&) const = 0;
};

}//namespace srng
