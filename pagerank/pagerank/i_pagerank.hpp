#pragma once

#include <unordered_map>
#include <string>

namespace srng{

class IPagerank
{
public:
    virtual ~IPagerank() = default;
    virtual void update(std::unordered_map<std::string, double> const&) = 0;
    virtual double get(std::string const&) const = 0;
};

}//namespace srng
