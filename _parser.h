#pragma once

#include "asm_optimizer.h"
#include "statement.h"
#include "lexer.h"
#include "node.h"

class Parser
{
private:
    Lexer lexer;
    Generator generator;
    AsmOptimizer asmOptimizer;

    SymTableStack symStack;
    vector <SyntaxNode*> nodeStack;
    vector <Statement*> stmtStack;

    map <TokenType, int> precedences;
    map <TokenType, bool> unary_oper;
    map <TokenType, bool> right_assoc_oper;

    vector <SyntaxNode*> consts;

public:
    Parser(const char*, const char*);
    ~Parser();

    void Init();

    bool Eof();
    void Next();

    BaseToken* GetUnary();

    void Parse();
    void GenerateCode(bool withAsmOptimization = false);
    void AsmOptimization();

    void ParseDeclaration();
    SymType* ParseTypeSpecifier();

    void ParseStructDeclaration();
    SymTypeStruct* ParseStructSpecifier();

    SymVar* ParseDeclarator(SymType*, bool parseParams = false);

    void ParseParameterList();

    Statement* ParseStatement();
    StmtBlock* ParseBlock(bool flag = false);
    StmtIf* ParseIf();
    StmtFor* ParseFor();
    StmtWhile* ParseWhile();
    StmtJump* ParseJump();

    SyntaxNode* GetCondition();

    SyntaxNode* ParseExpression(int precedence = 0);
    SyntaxNode* ParsePrimaryExpression();
    SyntaxNode* ParsePrintf(BaseToken*);
    void ParseFuncCall(SyntaxNode*&);
    void ParseArrIndex(SyntaxNode*&);
    void ParseMemberSelection(SyntaxNode*&, BaseToken*);

    void Error(const char*);
    void Error(const string);
    void Expected(TokenType, TokenType);
    void Expected(bool, const char*);

    void PrintTree(SyntaxNode*, int, int, ostream&);
    void PrintStmtTrees(int, int, ostream&);
    void PrintNodeTrees(int, int, ostream&);
    void PrintSymTables(ostream&);

    int counter;
    SymTypeFunc* parseFunc;
    StmtIteration* parseIter;
};
