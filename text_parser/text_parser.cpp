#include <iostream>
#include <sstream>
#include <algorithm>

#include <gumbo.h>

#include "text_parser.hpp"

namespace srng{

void TextParser::parse(std::string html, std::vector<std::string>& words) const
{
    GumboOutput* output = gumbo_parse(html.c_str());
    words = cleantext(output->root);
}

bool isnt_char_of_word(char c)
{
    return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

std::vector<std::string> TextParser::cleantext(GumboNode *node) const
{
    std::vector<std::string> result;
    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_P) 
    {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) 
        {
            if(static_cast<GumboNode*>(children->data[i])->type == GUMBO_NODE_TEXT)
            {
                std::stringstream ss(static_cast<GumboNode*>(children->data[i])->v.text.text);
                std::string word;
                while(ss >> word)
                {
                    word.erase(std::remove_if(word.begin(), word.end(), isnt_char_of_word), word.end());    
                    if(word.begin() != word.end())
                    {
                        std::string lower_case;
                        for (size_t i = 0; i < word.size(); i++) 
                        {
                            lower_case.push_back(tolower(word[i]));
                        }
                        result.push_back(lower_case);
                    }
                }
            }
        }
    } 
    else if (node->type == GUMBO_NODE_ELEMENT &&
               node->v.element.tag != GUMBO_TAG_SCRIPT &&
               node->v.element.tag != GUMBO_TAG_STYLE) 
    {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) 
        {
            std::vector<std::string> recursion_result = cleantext(static_cast<GumboNode*>(children->data[i]));
            result.insert(result.end(), recursion_result.begin(), recursion_result.end());
        }
    }
    return result;
}

}//namespace srng
