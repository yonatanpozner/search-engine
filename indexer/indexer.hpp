#pragma once

#include "i_indexer.hpp"

namespace srng{

class IIndex;

class Indexer : public IIndexer
{
public:
    explicit Indexer(IIndex & index);
    virtual void update(std::vector<std::string> const& words, std::string const& url) const override;

private:
    IIndex & m_index;
};

}//namespace srng
