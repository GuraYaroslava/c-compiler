#pragma once

#include "lexer.h"
#include "node.h"

class SimpleParser
{
private:
    Lexer lexer;

public:
    SimpleParser(const char*);
    ~SimpleParser();

    bool Eof();

    Node* ParseExpr();
    Node* ParseTerm();
    Node* ParseFactor();
    void PrintTree(Node*, int, int, ostream&);
};