#pragma once

#include <vector>
#include <unordered_map>

#include "i_pagerank_factory.hpp"

namespace srng{

class IWebGraph;
class IPagerank;

class PagerankFactory : public IPagerankFactory
{
public:
    explicit PagerankFactory(IWebGraph &, IPagerank &, size_t);
    virtual void update() const override;

private:
    void updates_the_proportion_each_source_gives_to_each_target(std::unordered_map<std::string, std::unordered_map<std::string, double>>&) const;
    void fill_initial_values_of_rank(std::unordered_map<std::string, std::unordered_map<std::string, double>> const&, std::unordered_map<std::string, double>&) const;
    std::unordered_map<std::string, double> calculate_one_iteration_of_rank(std::unordered_map<std::string, std::unordered_map<std::string, double>> const&, std::unordered_map<std::string, double> &) const;
    bool there_was_a_change_in_the_rank(std::unordered_map<std::string, double> const&, std::unordered_map<std::string, double> &) const;

private:
    IWebGraph & m_webgraph;
    IPagerank & m_pagerank;
    size_t m_amount_of_iteration_of_pagerank_calculation;
};

double absolute(double);

}//namespace srng
