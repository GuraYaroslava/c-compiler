#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
using namespace std;

class Exception
{
public:
    int line, pos;
    string msg;
    Exception(int, int, string);
    string GetException();
};

#endif EXCEPTION_H