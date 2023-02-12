#pragma once

#include <unordered_map>
#include <string>
#include <mutex>

#include "i_pagerank.hpp"

namespace srng{

class Pagerank : public IPagerank
{
public:
    virtual void update(std::unordered_map<std::string, double> const&) override;
    virtual double get(std::string const&) const override;

private:
    std::unordered_map<std::string, double> m_Pagerank;
    mutable std::mutex m_mutex;
};

}//namespace srng
