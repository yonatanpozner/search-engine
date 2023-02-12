#pragma once

#include <string>

namespace srng{

class Configuration;
class ISearchIO;
class ICrawler;

class Application
{
public:
    explicit Application(Configuration const&, ISearchIO &, ICrawler &);
    void run()const;

private:
    size_t m_amount_of_crawling;
    std::string m_main_page;

    ISearchIO & m_search_io;
    ICrawler & m_crawler;
};

}//namespace srng
