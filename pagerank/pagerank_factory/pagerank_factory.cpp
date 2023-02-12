
#include <string>

#include "pagerank_factory.hpp"
#include "web_graph.hpp"
#include "pagerank.hpp"

namespace srng{

PagerankFactory::PagerankFactory(IWebGraph & webgraph, IPagerank & pagerank, size_t amount)
: m_webgraph(webgraph)
, m_pagerank(pagerank)
, m_amount_of_iteration_of_pagerank_calculation(amount)
{}

void PagerankFactory::update() const
{
    std::optional<std::unordered_map<std::string, std::unordered_map<std::string, double>>> graph_optional = m_webgraph.get();
    if(graph_optional)
    {
        std::unordered_map<std::string, std::unordered_map<std::string, double>> graph = graph_optional.value();
        
        updates_the_proportion_each_source_gives_to_each_target(graph);
        
        std::unordered_map<std::string, double> rank;
        fill_initial_values_of_rank(graph, rank);
        std::unordered_map<std::string, double> new_rank = calculate_one_iteration_of_rank(graph, rank);

        size_t counter = 0;
        while(there_was_a_change_in_the_rank(new_rank, rank) && counter < 80)
        {
            rank = new_rank;
            new_rank = calculate_one_iteration_of_rank(graph, rank);
            counter++;
        }

        m_pagerank.update(new_rank);
    }
}

void PagerankFactory::updates_the_proportion_each_source_gives_to_each_target(std::unordered_map<std::string, std::unordered_map<std::string, double>> & graph) const
{
    for(auto & source : graph)
    {
        double sum_of_links = 0.0;
        for(auto & destination : source.second)
        {
            sum_of_links += destination.second;
        }
        for(auto & destination : source.second)
        {
            destination.second /= sum_of_links;
        }
    }
}

void PagerankFactory::fill_initial_values_of_rank(std::unordered_map<std::string, std::unordered_map<std::string, double>> const & graph, std::unordered_map<std::string, double> & rank) const
{
    for(auto & link : graph)
    {
        rank[link.first] = 1.0/static_cast<double>(graph.size());
    }
}

std::unordered_map<std::string, double> PagerankFactory::calculate_one_iteration_of_rank(std::unordered_map<std::string, std::unordered_map<std::string, double>> const & graph, std::unordered_map<std::string, double> & previous_rank) const
{
    std::unordered_map<std::string, double> new_rank;
    for(auto const& map : graph)
    {
        for(auto const& link : map.second)
        {
            new_rank[link.first] += 0.85*link.second*previous_rank[map.first];
        }
    }
    for(auto & link : new_rank)
    {
        link.second += 0.15/static_cast<double>(new_rank.size());
    }
    return new_rank;
}

bool PagerankFactory::there_was_a_change_in_the_rank(std::unordered_map<std::string, double> const & previous_rank, std::unordered_map<std::string, double> & rank) const
{
    for(auto const& link : previous_rank)
    {
        if(absolute(link.second - rank[link.first]) < 0.001)
        {
            return true;
        }
    }
    return false;
}

double absolute(double a)
{
    if(a < 0.0)
    {
        return -a;
    }
    return a;
}

} // namespace srng
