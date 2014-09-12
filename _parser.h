#pragma once

#include "scanner.h"
#include "symbol.h"
#include "lexer.h"
#include "node.h"

class Parser
{
private:
    Lexer lexer;
    SymTableStack symStack;
    vector <SyntaxNode*> nodeStack;

    map<TokenType, int> precedences;
    map<TokenType, bool> unary_oper;
    map<TokenType, bool> right_assoc_oper;

public:
    Parser(const char*);
    ~Parser();

    void Init();

    bool Eof();

    BaseToken* GetUnary();

    void Parse(ostream&);

    void ParseDeclaration();
    SymType* ParseTypeSpecifier();

    void ParseStructDeclaration();
    SymTypeStruct* ParseStructSpecifier();

    SymVar* ParseDeclarator(SymType*, bool parseParams = false);

    void ParseParameterList();

    SyntaxNode* ParseExpression(int precedence = 0);
    SyntaxNode* ParsePrimaryExpression();
    void ParseFuncCall(SyntaxNode*&);
    void ParseArrIndex(SyntaxNode*&);
    void ParseMemberSelection(SyntaxNode*&, BaseToken*);

    void Error(const char*);
    void Error(const string);

    void PrintTree(SyntaxNode*, int, int, ostream&);
    void PrintNodeTrees(int, int, ostream&);
    void PrintSymTables(ostream&);
};
