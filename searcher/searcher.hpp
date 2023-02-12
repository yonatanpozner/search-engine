#pragma once

#include "i_searcher.hpp"

namespace srng{

class IIndex;
class IPagerank;

class Searcher : public ISearcher
{
public:
    explicit Searcher(IIndex &, IPagerank &, size_t &);
    std::vector<std::pair<double, std::string>> search(std::pair<std::vector<std::string>, std::vector<std::string>> &) const override;

private:
    void remove_unshered_links(std::unordered_map<std::string, double> const&, std::vector<std::pair<std::string, double>> &) const;
    void remove_shered_links(std::unordered_map<std::string, double> const&, std::vector<std::pair<std::string, double>> &) const;
    void multiply_value_by_rank(std::vector<std::pair<std::string, double>>&) const;
    std::vector<std::pair<double, std::string>> get_first_elements(std::vector<std::pair<std::string, double>>const&) const;
    static bool compare(std::pair<std::string, double> const&, std::pair<std::string, double> const&);
    
private:
    IIndex & m_index;
    IPagerank & m_pagerank;

    size_t m_amount_of_result;
};

}//namespace srng
