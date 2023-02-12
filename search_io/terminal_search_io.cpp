#include <vector>
#include <iostream>
#include <bits/stdc++.h>

#include "terminal_search_io.hpp"
#include "searcher.hpp"

namespace srng{

TerminalSeachIO::TerminalSeachIO(ISearcher const& searcher)
: m_searcher(searcher)
{}

void TerminalSeachIO::get_input_search_send_output()
{
    for(;;)
    {
        std::pair<std::vector<std::string>, std::vector<std::string>> input = get_input();
        std::vector<std::pair<double, std::string>> result = m_searcher.search(input);
        send_output(result);
    }
}

std::pair<std::vector<std::string>, std::vector<std::string>> TerminalSeachIO::get_input()
{
    std::vector<std::string> search_terms;
    std::vector<std::string> out_of_text;

    std::cout << "enter your search terms :\n";
    std::string terms;
    getline (std::cin, terms);
    std::istringstream ss(terms);
    std::string word;
    while (ss >> word)
    {
        if(word[0] == '-')
        {
            word.erase(word.begin());
            out_of_text.push_back(word);
        }
        else
        {
            search_terms.push_back(word);
        }
    }
    return {search_terms, out_of_text};
}

void TerminalSeachIO::send_output(std::vector<std::pair<double, std::string>> const & output)
{
    for(auto const& url : output)
    {
        std::cout << url.first << " :\t" << url.second << "\n";
    }
}

}//namespace srng
