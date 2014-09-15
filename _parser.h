#pragma once

#include "statement.h"
#include "lexer.h"
#include "node.h"

class Parser
{
private:
    Lexer lexer;
    SymTableStack symStack;
    vector <SyntaxNode*> nodeStack;
    vector <Statement*> stmtStack;

    map<TokenType, int> precedences;
    map<TokenType, bool> unary_oper;
    map<TokenType, bool> right_assoc_oper;

public:
    Parser(const char*);
    ~Parser();

    void Init();

    bool Eof();

    BaseToken* GetUnary();

    void Parse();

    void ParseDeclaration();
    SymType* ParseTypeSpecifier();

    void ParseStructDeclaration();
    SymTypeStruct* ParseStructSpecifier();

    SymVar* ParseDeclarator(SymType*, bool parseParams = false);

    void ParseParameterList();

    Statement* ParseStatement();
    //StmtExpr* ParseExpr();
    StmtBlock* ParseBlock();
    StmtIf* ParseIf();
    StmtFor* ParseFor();
    StmtWhile* ParseWhile();
    StmtJump* ParseJump();

    SyntaxNode* GetCondition();

    SyntaxNode* ParseExpression(int precedence = 0);
    SyntaxNode* ParsePrimaryExpression();
    void ParseFuncCall(SyntaxNode*&);
    void ParseArrIndex(SyntaxNode*&);
    void ParseMemberSelection(SyntaxNode*&, BaseToken*);

    void Error(const char*);
    void Error(const string);
    void Expected(TokenType, TokenType);

    void PrintTree(SyntaxNode*, int, int, ostream&);
    void PrintStmtTrees(int, int, ostream&);
    void PrintNodeTrees(int, int, ostream&);
    void PrintSymTables(ostream&);

    bool inLoop;
    bool parseFunc;
};
