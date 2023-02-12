
#include "indexer.hpp"
#include "index.hpp"

namespace srng{

Indexer::Indexer(IIndex & index)
: m_index(index)
{}

void Indexer::update(std::vector<std::string> const& words, std::string const& url) const
{
    for(std::string const& word : words)
    {
        m_index.insert(word, url);
    }
}

}//namespace srng
