#pragma once

#include <exception>
#include <string>

namespace srng{

class ExitException : public std::exception
{
public:
    ExitException(std::string &&);
    char const * what();
private:
    std::string m_what;
};

inline ExitException::ExitException(std::string && what)
: m_what(what)
{}

inline char const * ExitException::what()
{
    return m_what.c_str();
}

}//namespace srng
