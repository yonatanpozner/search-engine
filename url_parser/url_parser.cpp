#include <iostream>
#include <gumbo.h>
#include <regex>
#include <optional>

#include "url_parser.hpp"

namespace srng{

UrlParser::UrlParser(std::string& main_page_link)
: m_main_page_link(main_page_link)
, m_webside_name(extracting_webside_name(main_page_link))
{}

void UrlParser::parse(std::string html, std::vector<std::string>& links) const
{
    GumboOutput* output = gumbo_parse(html.c_str());
    get_links_from_html(output->root, links);
}

void UrlParser::get_links_from_html(GumboNode* node, std::vector<std::string> & links) const
{
    if (node->type != GUMBO_NODE_ELEMENT)
        return;

    if (node->v.element.tag == GUMBO_TAG_A)
    {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
        if (href)
        {
            std::optional<std::string> fixed_link = fixing_link(href->value);
            if(fixed_link)
            {
                links.push_back(fixed_link.value());
            }
        }
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; i++)
    {
        get_links_from_html(static_cast<GumboNode*>(children->data[i]), links);
    }
}

std::optional<std::string> UrlParser::fixing_link(std::string const& link) const
{
    std::optional<std::string> fixed_link;
    if(is_internal_link(link))
    {
        if(link.find(m_webside_name) != link.npos)
        {
            fixed_link = link;
        }
        else if(link.find("http") == link.npos && link.find("#") == link.npos)
        {
            fixed_link = m_webside_name + link;
        }
    }
    return fixed_link;
}

std::string UrlParser::extracting_webside_name(std::string const& main_page_link) const
{
    std::regex rgxwebname("//(.+?)/");
    std::smatch match;
    std::regex_search(main_page_link, match, rgxwebname);

    return "https://" + match[1].str();
}

bool UrlParser::is_internal_link(std::string const& link) const
{
    return link.find(m_webside_name) != link.npos ||
          link.find("http") == link.npos;
}

}//namespace srng