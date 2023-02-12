#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include "loader.hpp"

using namespace std;

namespace srng{

struct Configuration;

class FileLoader : public ConfigurationLoader
{
public:
    explicit FileLoader(std::string file_name);
    virtual Configuration get_configuration() override;

private:
    void set_main_page_link(std::ifstream & file, Configuration & config)const;
    void set_size_of_crewling(std::ifstream & file, Configuration & config)const;
    void set_amount_of_results(std::ifstream & file, Configuration & config)const;
    void set_amount_of_threads(std::ifstream & file, Configuration & config)const;
    void set_amount_of_connections(std::ifstream & file, Configuration & config)const;
    void set_amount_of_attempts_to_connection(std::ifstream & file, Configuration & config)const;
    void set_amount_of_iteration_of_pagerank_calculation(std::ifstream & file, Configuration & config)const;
    void set_pagerank_update_frequency(std::ifstream & file, Configuration & config)const;

    string line_lexer(std::string const& line)const;

private:
    std::string const m_file_name;
};

}//namespace srng

#endif
