#pragma once

#include <map>
#include <string>
using namespace std;

#include "statement.h"
#include "scanner.h"
#include "symbol.h"
#include "token.h"
#include "node.h"

class Parser;

class Lexer
{
private:
    Scanner scanner;
    BaseToken* prep;
    BaseToken* last;

public:
    Lexer(const char*);
    ~Lexer();

    BaseToken* Get();
    BaseToken* Peek();
    void UnGet();
    int GetPos();
    int GetLine();

    friend Parser;
};

class Parser
{
public:
    int begin;
    SymType* curr_type;
    TokenType curr_stmt;
    SymTableStack* stack;
    vector <BaseToken*> dcl;
    vector <Statement*> stmt;
    map<TokenType, bool> unary_oper;
    map<TokenType, int> priority_table;
    map<TokenType, bool> right_assoc_oper;

public:
    Parser(const char*);
    ~Parser();
    Lexer lexer;

    SyntaxNode* ParseExpression(int);
    SyntaxNode* ParseFactor();
    void ParseFuncCall(SyntaxNode*&, BaseToken*&);

    void Parse(vector <Statement*>&);
    Statement* ParseStatement();
    Statement* GetStmtAssignment();
    StmtBlock* ParseBlock();
        
    Statement* ParseDeclaration();
    void ParseDeclarator();
    void ParseDirectDeclarator();
    Symbol* Translator(int end);

    SymType* ParseType();
    SymType* ParseTypeStruct();
    void ParseTypeArray();
        
    string GetRandomName();
    void Init();

    void Error(const char*);
    void Error(const string);

    void PrintTree(SyntaxNode*, int, int, ostream&);
    void PrintSymbols(ostream&);

    friend NodeVar;
};