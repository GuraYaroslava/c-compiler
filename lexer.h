#pragma once

#include "scanner.h"

class Lexer
{
private:
    Scanner scanner;
    BaseToken* prep;
    BaseToken* last;

public:
    Lexer(const char*);
    ~Lexer();

    int GetPos();
    int GetLine();

    BaseToken* Peek();
    BaseToken* Get();
    void UnGet();
};