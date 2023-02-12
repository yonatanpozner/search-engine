#ifndef INDEX_HPP
#define INDEX_HPP

#include <unordered_map>
#include <map>

#include <mutex>

#include "i_index.hpp"

namespace srng{

class Index : public IIndex
{
public:
    virtual void insert(std::string const& word, std::string const& url) override;
    virtual void get_urls(std::string const& word, std::unordered_map<std::string, double>& urls) const override;
    virtual void get_urls(std::string const& word, std::vector<std::pair<std::string, double>>& urls) const override;
private:
    mutable std::mutex m_mutex;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> m_data_base;
};

}//namespace srng

#endif
