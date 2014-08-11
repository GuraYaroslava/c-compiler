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