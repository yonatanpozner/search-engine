#pragma once

#include <vector>
#include <string>

namespace srng{

class ITextParser
{
public:
    virtual ~ITextParser() = default;
    virtual void parse(std::string, std::vector<std::string>&) const = 0;
};

}//namespace srng
