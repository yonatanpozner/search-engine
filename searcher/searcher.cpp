#include <algorithm>
#include <iostream>
#include <map>

#include "searcher.hpp"
#include "pagerank.hpp"
#include "index.hpp"

namespace srng{

Searcher::Searcher(IIndex & index, IPagerank & Pagerank, size_t & amount_of_result)
: m_index(index)
, m_pagerank(Pagerank)
, m_amount_of_result(amount_of_result)
{}

std::vector<std::pair<double, std::string>> Searcher::search(std::pair<std::vector<std::string>, std::vector<std::string>> & search_words_and_out_of_text_words) const
{
    std::vector<std::string> search_words = search_words_and_out_of_text_words.first;
    std::vector<std::pair<std::string, double>> vector_of_union_links;
    if(search_words.size())
    {
        m_index.get_urls(search_words[0], vector_of_union_links);
        for(size_t i = 1; i < search_words.size(); ++i)
        {
            std::unordered_map<std::string, double> links_of_word;
            m_index.get_urls(search_words[i], links_of_word);
            remove_unshered_links(links_of_word, vector_of_union_links);
        }
    }

    std::vector<std::string> out_of_text = search_words_and_out_of_text_words.second;
    for(size_t i = 0; i < out_of_text.size(); ++i)
    {
        std::unordered_map<std::string, double> links_of_word;
        m_index.get_urls(out_of_text[i], links_of_word);
        remove_shered_links(links_of_word, vector_of_union_links);
    }
    
    multiply_value_by_rank(vector_of_union_links);
   
    std::sort(vector_of_union_links.begin(), vector_of_union_links.end(), compare);
    
    return get_first_elements(vector_of_union_links);
}

void Searcher::remove_unshered_links(std::unordered_map<std::string, double> const& new_links, std::vector<std::pair<std::string, double>> & links) const
{
    auto begin = links.begin();
    while(begin != links.end())
    {
        if(!new_links.count((*begin).first))
        {
            begin = links.erase(begin);
        }
        else
        {
            std::string url = (*begin).first;
            (*begin).second = std::min((*begin).second, new_links.at(url));
            ++begin;
        }
    }
}

void Searcher::remove_shered_links(std::unordered_map<std::string, double> const& new_links, std::vector<std::pair<std::string, double>> & links) const
{
    auto begin = links.begin();
    while(begin != links.end())
    {
        if(new_links.count((*begin).first))
        {
            begin = links.erase(begin);
        }
        else
        {
            ++begin;
        }
    }
}

void Searcher::multiply_value_by_rank(std::vector<std::pair<std::string, double>> & links) const
{
    for(auto & link : links)
    {
        link.second *= m_pagerank.get(link.first);
    }
}

std::vector<std::pair<double, std::string>> Searcher::get_first_elements(std::vector<std::pair<std::string, double>> const& vector_of_union_links) const
{
    auto begin = vector_of_union_links.begin();
    auto end = vector_of_union_links.end();
    std::vector<std::pair<double, std::string>> result;
    size_t counter = 0;
    while(begin != end && counter < m_amount_of_result)
    {
        result.push_back({(*begin).second, (*begin).first});
        ++counter;
        ++begin;
    }
    return result;
}

bool Searcher::compare(std::pair<std::string, double> const& a, std::pair<std::string, double> const& b)
{
    return a.second > b.second;
}

}//namespace srng
