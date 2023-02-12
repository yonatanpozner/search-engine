#pragma once

#include "i_search_io.hpp"

namespace srng{

class ISearcher;

class TerminalSeachIO :public ISearchIO
{
public:
    explicit TerminalSeachIO(ISearcher const&);
    void get_input_search_send_output() override;

private:
    std::pair<std::vector<std::string>, std::vector<std::string>> get_input();
    void send_output(std::vector<std::pair<double, std::string>>const&);
    
private:
    ISearcher const& m_searcher;
};

}//namespace srng
