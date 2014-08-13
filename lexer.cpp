#include "lexer.h"

Lexer::Lexer(const char* fin): scanner(fin), prep(NULL), last(NULL) {}

Lexer::~Lexer() {}

int Lexer::GetPos()
{
    return scanner.curr_pos;
}

int Lexer::GetLine()
{
    return scanner.curr_line;
}

BaseToken* Lexer::Peek()
{
    BaseToken* token = Get();
    UnGet();
    return token;
}

BaseToken* Lexer::Get()
{
    last = prep ? prep : scanner.Next();
    prep = 0;
    return last;
}

void Lexer::UnGet()
{
    if (!last) return;
    prep = last;
    last = 0;
}