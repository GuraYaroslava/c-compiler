#include <string>
#include <sstream>
#include "exception.h"
using namespace std;

Exception::Exception(int _line, int _pos, string _msg)
{
    line = _line;
    pos = _pos;
    msg = _msg;
}

Exception::Exception(string msg_):
    line(-1),
    pos(-1),
    msg(msg_)
    {}


string Exception::GetException()
{
    if (line < 0 || pos < 0)
    {
        return msg;
    }
    stringstream l, p;
    l << line;
    p << pos+1;
    string ans = "[Ln: " + l.str() + ", Col: " + p.str() + "] Error: " + msg;
    return ans;
}