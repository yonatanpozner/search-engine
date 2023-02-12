#pragma once

#include <optional>

#include "i_url_parser.hpp"

namespace srng{

typedef struct GumboInternalNode GumboNode;

class UrlParser : public IUrlParser
{
public:
    explicit UrlParser(std::string&);
    void parse(std::string, std::vector<std::string>&) const override;

private:
    void get_links_from_html(GumboNode*, std::vector<std::string>&) const;
    std::optional<std::string> fixing_link(std::string const&) const;
    std::string extracting_webside_name(std::string const&) const;
    bool is_internal_link(std::string const&) const;

private:
    std::string m_main_page_link;
    std::string m_webside_name;
};

}//namespace srng
