#include <regex>
#include <thread>

#include "application.hpp"
#include "configuration.hpp"
#include "crawler.hpp"
#include "terminal_search_io.hpp"
#include "network_search_io.hpp"

namespace srng{

Application::Application(Configuration const& config, ISearchIO & search_io, ICrawler & crawler)
: m_amount_of_crawling(config.size_of_clawling)
, m_main_page(config.main_page)
, m_search_io(search_io)
, m_crawler(crawler)
{}

void Application::run()const
{
    std::thread crawl([](ICrawler & crawler, std::string const& main_page){crawler.crawl(main_page);},std::ref(m_crawler), m_main_page);
    m_search_io.get_input_search_send_output();
    crawl.join();
}

}//namespace srng
