
#include "pagerank.hpp"


namespace srng{

void Pagerank::update(std::unordered_map<std::string, double> const& Pagerank)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    m_Pagerank = Pagerank;
}

double Pagerank::get(std::string const & page) const
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(!m_Pagerank.count(page))
    {
        return 0.0;
    }
    return m_Pagerank.at(page);
}

}//namespace srng
