#pragma once

#include "_parser_base.h"
#include "asm_optimizer.h"
#include "statement.h"
#include "lexer.h"
#include "node.h"

const int INF = numeric_limits<int>::max();

class Parser: public BaseParser
{
private:
    Lexer lexer;
    Generator generator;
    AsmOptimizer asmOptimizer;

    SymTableStack symStack;
    vector <Statement*> stmtStack;//!!!

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
    void SetUnUsed(const string&);
    void PushLocals(SymTable*);
    void PopLocals();

    void Parse();
    void GenerateCode(bool withAsmOptimization = false);
    void AsmOptimize();
    void Optimize();

    void ParseDeclaration();
    SymType* ParseTypeSpecifier();

    void ParseStructDeclaration();
    SymTypeStruct* ParseStructSpecifier();

    SymVar* ParseDeclarator(SymType*, bool parseParams = false);

    void ParseParameterList();

    Statement* ParseStatement();
    StmtBlock* ParseBlock(bool inFanction = false);
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

    void PrintStmtTrees(int, ostream&);//!!!
    void PrintSymTables(ostream&);

    int counter; //for generation nodes ids
    vector <SymTypeFunc*> parseFunc; //parsed whether the function at this time?
    StmtIteration* parseIter; //parsed whether the iteration at this time?

    friend class StmtBlock;
};
