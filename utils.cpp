#include "utils.h"
#include <sstream>

std::string ChToStr(char ch)
{
    std::stringstream ss;
    std::string str;
    ss << ch;
    ss >> str;
    return str;
}

bool isalpha_(char ch)
{
    if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ch == '_')
    {
        return true;
    }
    return false;
}

bool isdigit_(char ch)
{
    if ('0' <= ch && ch <= '9')
    {
        return true;
    }
    return false;
}

bool isasciich_(char ch)
{
    if ('0' <= (int)ch && (int)ch <= '255')
    {
        return true;
    }
    return false;
}
