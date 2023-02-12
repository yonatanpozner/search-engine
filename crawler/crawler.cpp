#include <thread>
#include <optional>
#include <utility>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "crawler.hpp"

#include "indexer.hpp"
#include "url_parser.hpp"
#include "text_parser.hpp"
#include "web_graph.hpp"
#include "pagerank_factory.hpp"
#include "safe_synchronization.hpp"

namespace srng{

Crawler::Crawler(IIndexer const& indexer, IWebGraph & web_graph, IPagerankFactory const& pagerank_factory, IUrlParser const& url_parser, ITextParser const& text_parser, ISafeQueue<std::string> & safe_queue, ISafeUnorderedSet<std::string> & safe_unoredred_set, ISafeSynchronization & safe_synchronization, size_t const& size_of_crawling, size_t const& amount_of_threads)
: m_indexer(indexer)
, m_url_parser(url_parser)
, m_text_parser(text_parser)
, m_web_graph(web_graph)
, m_pagerank_factory(pagerank_factory)
, m_size_of_crawling(size_of_crawling)
, m_amount_of_threads(amount_of_threads)
, m_next_links(safe_queue)
, m_previouses(safe_unoredred_set)
, m_mode_of_threads(safe_synchronization)
, m_counter_of_crawling(0)
{}

void Crawler::crawl(std::string const& url)
{
    auto lamda = [this](size_t index_of_thread){this->thread_crawl(index_of_thread); std::cout << "finish of thread\n";};

    m_next_links.push(url);
    m_previouses.insert(url);

    std::vector<std::thread> threads;
    for(size_t i = 0; i < m_amount_of_threads; ++i)
    {
        m_mode_of_threads.add_thread_mode();
        threads.push_back(std::thread(lamda, i));
    }
    for(auto& thread : threads)
    {
        thread.join();
    }
    std::cout << "\n--> the crawling finished.\n\n";
}

void Crawler::thread_crawl(size_t index_of_thread)
{
    while(m_counter_of_crawling < m_size_of_crawling && (m_mode_of_threads || m_next_links.size()))
    {
        auto link_to_crawl = m_next_links.pop();
        crawl_single_page(link_to_crawl, index_of_thread);
        m_counter_of_crawling++;
    }
}

void Crawler::crawl_single_page(std::string const& link, size_t const& index_of_thread)
{
    try
    {
        std::string html = get_html_by_link(link);
        
        std::vector<std::string> words;
        m_text_parser.parse(html, words);
        m_indexer.update(words, link);

        std::vector<std::string> links;
        m_url_parser.parse(html, links);
        update_queue(links);

        m_web_graph.update(link, links);
        
        m_pagerank_factory.update();

        bool mode = true;
        if(!links.size())
        {
            mode = false;
        }
        m_mode_of_threads.update_mode_at(index_of_thread, mode);
    }
    catch(...)
	{
        std::cout << "ERROR: bad link --> " << link << "\n";
	}
}

std::string Crawler::get_html_by_link(std::string const& link) const
{
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    std::string html;
    myRequest.setOpt<curlpp::options::Url>(link);
    myRequest.setOpt(curlpp::options::WriteFunction([&](char *data, size_t size, size_t nmemb) {
        html.append(data, size * nmemb);
        return size * nmemb;
    }));
    myRequest.perform();
    return html;
}

void Crawler::update_queue(std::vector<std::string> const& links)
{
    for(auto & link : links)
    {
        if(m_previouses.insert(link).second)
        {
            m_next_links.push(link);
        }
    }
}

}//namespace srng
