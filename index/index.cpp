#include <iostream>

#include "index.hpp"

namespace srng{

void Index::insert(std::string const& word, std::string const& url) 
{
    std::lock_guard<std::mutex> locker(m_mutex);
    m_data_base[word][url]++;
}

void Index::get_urls(std::string const& word, std::unordered_map<std::string, double>& urls) const
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(m_data_base.count(word))
    {
        auto begin = m_data_base.at(word).cbegin();
        auto end = m_data_base.at(word).cend();
        while(begin != end)
        {
            urls[(*begin).first] = (*begin).second;
            ++begin;
        }
    }
}

void Index::get_urls(std::string const& word, std::vector<std::pair<std::string, double>>& urls) const
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(m_data_base.count(word))
    {
        auto begin = m_data_base.at(word).cbegin();
        auto end = m_data_base.at(word).cend();
        while(begin != end)
        {
            urls.push_back({(*begin).first, (*begin).second});
            ++begin;
        }
    }
}

}//namespace srng
