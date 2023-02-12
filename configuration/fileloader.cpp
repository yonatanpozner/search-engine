#include <fstream>
#include <iostream>

#include "configuration.hpp"
#include "fileloader.hpp"

namespace srng{

FileLoader::FileLoader(std::string file_name)
: m_file_name(file_name)
{}

Configuration FileLoader::get_configuration()
{
    std::ifstream file(m_file_name);
    if(!file.good())
    {
        std::cout << "\n\ncheck the name file\n\n";
        abort();
    }
    Configuration config;
    
    set_main_page_link(file, config);
    set_size_of_crewling(file, config);
    set_amount_of_results(file, config);
    set_amount_of_threads(file, config);
    set_amount_of_connections(file, config);
    set_amount_of_attempts_to_connection(file, config);

    return config;
}

void FileLoader::set_main_page_link(std::ifstream & file, Configuration & config)const
{
    std::string line;
    getline(file, line);
    config.main_page = line_lexer(line);
}

void FileLoader::set_size_of_crewling(std::ifstream & file, Configuration & config)const
{
    std::string line;
    getline(file, line);
    config.size_of_clawling = stoi(line_lexer(line));
}

void FileLoader::set_amount_of_results(std::ifstream & file, Configuration & config)const
{
    std::string line;
    getline(file, line);
    config.amount_of_results = stoi(line_lexer(line));
}

void FileLoader::set_amount_of_threads(std::ifstream & file, Configuration & config)const
{
    std::string line;
    getline(file, line);
    config.amount_of_threads = stoi(line_lexer(line));
}

void FileLoader::set_amount_of_connections(std::ifstream &file, Configuration &config) const
{
    std::string line;
    getline(file, line);
    config.amount_of_connections = stoi(line_lexer(line));
}

void FileLoader::set_amount_of_attempts_to_connection(std::ifstream &file, Configuration &config) const
{
    std::string line;
    getline(file, line);
    config.amount_of_attempts_to_connection = stoi(line_lexer(line));
}

void FileLoader::set_amount_of_iteration_of_pagerank_calculation(std::ifstream &file, Configuration &config) const
{
    std::string line;
    getline(file, line);
    config.amount_of_iteration_of_pagerank_calculation = stoi(line_lexer(line));
}

void FileLoader::set_pagerank_update_frequency(std::ifstream &file, Configuration &config) const
{
    std::string line;
    getline(file, line);
    config.pagerank_update_frequency = stoi(line_lexer(line));
}

std::string FileLoader::line_lexer(std::string const& line)const
{
    std::string instruction;
    std::string::const_iterator begin = line.begin();
    std::string::const_iterator end = line.end();
    while(*begin != ':')
    {
        ++begin;
    }
    begin += 2;
    while(begin != end)
    {
        instruction += *begin;
        ++begin;
    }
    return instruction;
}

}//namespace srng
