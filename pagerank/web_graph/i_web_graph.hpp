#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace srng{

class IWebGraph
{
public:
    virtual ~IWebGraph() = default;
    virtual void update(std::string const& source, std::vector<std::string> const& destinations) = 0;
    virtual std::optional<std::unordered_map<std::string, std::unordered_map<std::string, double>>> get() = 0;
};

}//namespace srng
