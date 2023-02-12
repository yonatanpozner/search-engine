
#include "web_graph.hpp"

namespace srng{

WebGraph::WebGraph(size_t amount)
: m_rankpage_update_frequency(amount)
{}

void WebGraph::update(std::string const &source, std::vector<std::string> const &destinations)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    for(auto const& destination : destinations)
    {
        m_graph[source][destination]++;
    }
    m_counter++;
}

std::optional<std::unordered_map<std::string, std::unordered_map<std::string, double>>> WebGraph::get()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(m_counter > m_rankpage_update_frequency)
    {
        m_counter = 0;
        return m_graph;
    }
    return {};
}

}//namespace srng
