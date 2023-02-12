#pragma once

#include <vector>
#include <string>

#include <SFML/Network.hpp>

#include "i_search_io.hpp"

namespace srng{

class ISearcher;

class NetworkSearchIO : public ISearchIO
{
public:
    explicit NetworkSearchIO(ISearcher&, sf::TcpListener &, size_t, size_t);
    virtual void get_input_search_send_output() override;

private:
    void threads_get_input_search_send_output(std::unique_ptr<sf::TcpSocket> socket);

    std::pair<std::vector<std::string>, std::vector<std::string>> get_input(sf::TcpSocket &);
    void send_output(std::vector<std::pair<double, std::string>>const&, sf::TcpSocket &);

    size_t create_output(char *, std::vector<std::pair<double, std::string>> const&)const;
    void request_search_terms(sf::TcpSocket &);
    void get_string_of_search_terms(std::string&, sf::TcpSocket &);

private:
    ISearcher & m_searcher;
    sf::TcpListener & m_listener;
    size_t m_amount_of_connections;
    size_t m_amount_of_attempts_to_connection;
};

}//namespace srng
