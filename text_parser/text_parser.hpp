#pragma once

#include "i_text_parser.hpp"

namespace srng{

typedef struct GumboInternalNode GumboNode;

class TextParser : public ITextParser
{
public:
    void parse(std::string html, std::vector<std::string>&) const override;

private:
    std::vector<std::string> cleantext(GumboNode* node) const ;
};

}//namespace srng