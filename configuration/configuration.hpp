#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

namespace srng{

struct Configuration
{
    std::string main_page;
    size_t size_of_clawling;
    size_t amount_of_results;
    size_t amount_of_threads;
    size_t amount_of_connections;
    size_t amount_of_attempts_to_connection;
    size_t amount_of_iteration_of_pagerank_calculation;
    size_t pagerank_update_frequency;
};

}//namespace srng

#endif
