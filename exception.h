#pragma once

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