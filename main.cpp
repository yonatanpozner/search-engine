#include <iostream>
#include <regex>
#include <gumbo.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "fileloader.hpp"
#include "configuration.hpp"
#include "index.hpp"
#include "indexer.hpp"
#include "text_parser.hpp"
#include "url_parser.hpp"
#include "safe_unordered_set.hpp"
#include "safe_queue.hpp"
#include "crawler.hpp"
#include "searcher.hpp"
#include "terminal_search_io.hpp"
#include "network_search_io.hpp"
#include "application.hpp"
#include "web_graph.hpp"
#include "pagerank.hpp"
#include "pagerank_factory.hpp"
#include "safe_synchronization/safe_synchronization.hpp"

using namespace srng;

void test_terminal_input_output()
{
    FileLoader fileloader("configuration/configuration.txt");
    Configuration config = fileloader.get_configuration();
    
    Index index;
    Indexer indexer(index);
    TextParser text_parser;
    UrlParser url_parser(config.main_page);
    SafeQueue<std::string> safe_queue;
    SafeUnorderedSet<std::string> safe_unordered_set;
    WebGraph web_graph(config.pagerank_update_frequency);
    Pagerank pagerank;
    PagerankFactory pagerank_factory(web_graph, pagerank, config.amount_of_iteration_of_pagerank_calculation);
    SafeSynchronization safe_synchronization;
    Crawler crawler(indexer, web_graph, pagerank_factory, url_parser, text_parser, safe_queue, safe_unordered_set, safe_synchronization, config.size_of_clawling, config.amount_of_threads);
    Searcher searcher(index, pagerank, config.amount_of_results);
    TerminalSeachIO search_io(searcher);
    Application application(config, search_io, crawler);
    application.run();
}

void test_network_input_output()
{
    FileLoader fileloader("configuration/configuration.txt");
    Configuration config = fileloader.get_configuration();
    
    Index index;
    Indexer indexer(index);
    TextParser text_parser;
    UrlParser url_parser(config.main_page);
    SafeQueue<std::string> safe_queue;
    SafeUnorderedSet<std::string> safe_unordered_set;
    WebGraph web_graph(config.pagerank_update_frequency);
    Pagerank pagerank;
    PagerankFactory pagerank_factory(web_graph, pagerank, config.amount_of_iteration_of_pagerank_calculation);
    SafeSynchronization safe_synchronization;
    Crawler crawler(indexer, web_graph, pagerank_factory, url_parser, text_parser, safe_queue, safe_unordered_set, safe_synchronization, config.size_of_clawling, config.amount_of_threads);
    Searcher searcher(index, pagerank, config.amount_of_results);
    sf::TcpListener listener;
    NetworkSearchIO search_io(searcher, listener, config.amount_of_connections, config.amount_of_attempts_to_connection);
    Application application(config, search_io, crawler);
    application.run();
}

int main()
{
    try
    {
        test_network_input_output();
    // test_terminal_input_output();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
