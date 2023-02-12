#pragma once

#include <mutex>

#include "i_web_graph.hpp"

namespace srng{

class WebGraph : public IWebGraph
{
public:
    explicit WebGraph(size_t);
    virtual void update(std::string const& source, std::vector<std::string> const& destinations) override;
    virtual std::optional<std::unordered_map<std::string, std::unordered_map<std::string, double>>> get() override;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, double>> m_graph;
    mutable std::mutex m_mutex;
    size_t m_counter;
    size_t m_rankpage_update_frequency;
};

}//namespace srng
