#pragma once

#include <string>

namespace srng{

class ICrawler
{
public:
    virtual ~ICrawler() = default;
    virtual void crawl(std::string const& url) = 0;
};

}//namespace srng
