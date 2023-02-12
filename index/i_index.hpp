#ifndef I_INDEX_HPP
#define I_INDEX_HPP

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

namespace srng{

class IIndex
{
public:
    virtual ~IIndex() = default;
    virtual void insert(std::string const& word, std::string const& url) = 0;
    virtual void get_urls(std::string const& word, std::unordered_map<std::string, double>& urls) const = 0;
    virtual void get_urls(std::string const& word, std::vector<std::pair<std::string, double>>& urls) const = 0;
};

}//namespace srng

#endif
