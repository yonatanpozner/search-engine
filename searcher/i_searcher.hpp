#pragma once

#include <vector>
#include <string>

namespace srng{

class ISearcher 
{
public:
    virtual ~ISearcher() = default;
    virtual std::vector<std::pair<double, std::string>> search(std::pair<std::vector<std::string>, std::vector<std::string>> &) const = 0;
};

}//namespace srng
