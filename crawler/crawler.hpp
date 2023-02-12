#pragma once

#include <string>
#include <queue>
#include <unordered_set>
#include <mutex>
#include <atomic>

#include "i_crawler.hpp"
#include "safe_queue.hpp"
#include "safe_unordered_set.hpp"


namespace srng{

class IIndexer;
class IUrlParser;
class ITextParser;
class IWebGraph;
class IPagerankFactory;
class ISafeSynchronization;

class Crawler : public ICrawler
{
public:
    explicit Crawler(IIndexer const&, IWebGraph &, IPagerankFactory const&, IUrlParser const&, ITextParser const&, ISafeQueue<std::string> &, ISafeUnorderedSet<std::string> &, ISafeSynchronization &, size_t const&, size_t const&);
    void crawl(std::string const& url) override;

private:
    void thread_crawl(size_t);
    void crawl_single_page(std::string const& link, size_t const&);
    std::string get_html_by_link(std::string const& link)const;
    void update_queue(std::vector<std::string> const&);

private:
    IIndexer const& m_indexer;
    IUrlParser const& m_url_parser;
    ITextParser const& m_text_parser;
    IWebGraph & m_web_graph;
    IPagerankFactory const& m_pagerank_factory;
    
    std::atomic<size_t> m_size_of_crawling;
    std::atomic<size_t> m_amount_of_threads;

    ISafeQueue<std::string> & m_next_links;
    ISafeUnorderedSet<std::string> & m_previouses;
    ISafeSynchronization & m_mode_of_threads;
    std::atomic<size_t> m_counter_of_crawling;
};

}//namespace srng
