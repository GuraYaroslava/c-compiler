#pragma once

#include "scanner.h"
#include "node.h"

class SimpleParser
{
public:
    Scanner scanner;

    SimpleParser(const char*);
    ~SimpleParser();

    Node* ParseExpr();
    Node* ParseTerm();
    Node* ParseFactor();
    void PrintTree(Node*, int, int, ostream&);
};