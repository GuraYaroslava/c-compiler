#pragma once

#include "scanner.h"
#include "lexer.h"
#include "node.h"

class Parser
{
private:
    Lexer lexer;

    map<TokenType, int> precedences;
    map<TokenType, bool> unary_oper;
    map<TokenType, bool> right_assoc_oper;

public:
    Parser(const char*);
    ~Parser();

    void Init();

    bool Eof();

    BaseToken* GetUnary();

    SyntaxNode* ParseExpression(int precedence = 0);
    SyntaxNode* ParsePrimaryExpression();
    //SyntaxNode* ParsePostfixExpression();

    void ParseFuncCall(SyntaxNode*&);
    void ParseArrIndex(SyntaxNode*&);
    void ParseMemberSelection(SyntaxNode*&, BaseToken*);

    void Error(const char*);
    void Error(const string);

    void PrintTree(SyntaxNode*, int, int, ostream&);
};