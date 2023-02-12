#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <memory>

#include "network_search_io.hpp"
#include "searcher.hpp"

namespace srng{

NetworkSearchIO::NetworkSearchIO(ISearcher & searcher, sf::TcpListener & listener, size_t amount_of_connections, size_t amount_of_attempts_to_connection)
: m_searcher(searcher)
, m_listener(listener)
, m_amount_of_connections(amount_of_connections)
, m_amount_of_attempts_to_connection(amount_of_attempts_to_connection)
{
    try
    {
        size_t counter = 0;
        while(counter < m_amount_of_attempts_to_connection)
        {
            if(m_listener.listen(8080) == sf::Socket::Done)
            {
                break;
            }
            counter++;
        }
        if(counter == m_amount_of_attempts_to_connection)
        {
            throw std::exception();
        }
    }
    catch(...)
    {
        throw;
    }
}

void NetworkSearchIO::get_input_search_send_output()
{
    auto lamda = [this](std::unique_ptr<sf::TcpSocket> socket){this->threads_get_input_search_send_output(std::move(socket));};
    
    std::vector<std::thread> threads;
    for(size_t i = 0; i < m_amount_of_connections; ++i)
    {
        std::unique_ptr<sf::TcpSocket> socket(new sf::TcpSocket());
        m_listener.accept(*socket);
        threads.push_back(std::thread(lamda, (std::move(socket))));
    }
    for(auto& thread : threads)
    {
        thread.join();
    }
}

void NetworkSearchIO::threads_get_input_search_send_output(std::unique_ptr<sf::TcpSocket> socket)
{
    try
    {
        for(;;)
        {
            std::pair<std::vector<std::string>, std::vector<std::string>> input = get_input(*socket);
            std::vector<std::pair<double, std::string>> result = m_searcher.search(input);
            send_output(result, *socket);
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::pair<std::vector<std::string>, std::vector<std::string>> NetworkSearchIO::get_input(sf::TcpSocket &socket)
{
    request_search_terms(socket);

    std::string string_received;
    get_string_of_search_terms(string_received, socket);

    std::vector<std::string> search_terms;
    std::vector<std::string> out_of_text;
    
    std::istringstream ss(string_received);
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

void NetworkSearchIO::send_output(std::vector<std::pair<double, std::string>> const & raw_output, sf::TcpSocket & socket)
{
    char output[1000];
    size_t bytes_to_send = create_output(output, raw_output);
    try
    {
        if (socket.send(output, bytes_to_send) != sf::Socket::Done)
        {
            throw std::runtime_error("The connection was disconnected");
        }
    }
    catch(const std::exception& e)
    {
        throw;
    }
}

size_t NetworkSearchIO::create_output(char * output, std::vector<std::pair<double, std::string>> const& raw_output)const
{
    std::string new_output;
    for(auto & result : raw_output)
    {
        new_output += std::to_string(result.first);
        new_output += " :\t";
        new_output += result.second;
        new_output += "\n";
    }

    if(!new_output.size())
    {
        new_output = "no result for your search\n";
    }
    
    for(size_t i = 0; i < new_output.size(); ++i)
    {
        output[i] = new_output[i];
    }
    return new_output.size();
}

void NetworkSearchIO::request_search_terms(sf::TcpSocket &socket)
{
    char request_search_terms[27] = "enter your search terms :\n";
    try
    {
        if(socket.send(request_search_terms, 27) != sf::Socket::Done)
        {
            throw std::runtime_error("The connection was disconnected");
        }
    }
    catch(std::exception const& e)
    {
        throw;
    }
}

void NetworkSearchIO::get_string_of_search_terms(std::string & string_received, sf::TcpSocket & socket)
{
    char characters_received[100];
    std::size_t received;

    try
    {
        if (socket.receive(characters_received, 100, received) != sf::Socket::Done)
        {
            throw std::runtime_error("The connection was disconnected");
        }
    }
    catch(const std::exception& e)
    {
        throw;
    }
    
    for(size_t i = 0; i < received; ++i)
    {
        string_received += characters_received[i];
    }
    string_received += "\0";
}

}//namespace srng
