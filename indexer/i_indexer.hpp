#pragma once

#include <string>
#include <vector>

namespace srng{

class IIndexer
{
public:
    virtual ~IIndexer() = default;
    virtual void update(std::vector<std::string> const& words, std::string const& url) const = 0;
};

}// namespace srng
