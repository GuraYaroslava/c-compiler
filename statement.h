#ifndef _STATEMENT_H
#define _STATEMENT_H

#include "node.h"
class SymTable;
class SymFunc;
class Parser;

class Statement
{
public:
    Statement();
    ~Statement();

    virtual void StmtPrint(ostream &out/*, int*/);
};

class StmtAssignment: public Statement
{
private:
    SyntaxNode* left;
    SyntaxNode* right;

public:
    StmtAssignment(SyntaxNode*, SyntaxNode*);
    ~StmtAssignment();

    void StmtPrint(ostream &out/*, int*/);
};

class StmtBlock: public Statement
{
private:
    SymTable* locals;
    vector <Statement*> statements;

public:
    StmtBlock();
    ~StmtBlock();

    void StmtPrint(ostream &out/*, int*/);
    friend Parser;
    friend SymFunc;
};

class StmtExpr: public Statement
{
private:
    SyntaxNode* expr;

public:
    StmtExpr(SyntaxNode*);
    ~StmtExpr();
    void StmtPrint(ostream &out/*, /*int*/);
};

class StmtIf: public Statement
{
private:
    SyntaxNode* condition;
    Statement* if_body;
    Statement* else_body;

public:
    StmtIf(SyntaxNode*,  Statement*, Statement*);
    ~StmtIf();

    void StmtPrint(ostream &out/*, /*int*/);
};

class StmtFor: public Statement
{
private:
    StmtExpr *expr1;
    StmtExpr *expr2;
    StmtExpr *expr3;
    Statement* body;

public:
    StmtFor(SyntaxNode*, SyntaxNode*, SyntaxNode*, Statement*);
    StmtFor(StmtExpr*, StmtExpr*, StmtExpr*, Statement*);
    ~StmtFor();

    void StmtPrint(ostream &out/*, int*/);
};

class StmtWhile: public Statement
{
private:
    SyntaxNode* condition;
    Statement* body;

public:
    StmtWhile(SyntaxNode*, Statement*);
    ~StmtWhile();

    void StmtPrint(ostream &out/*, /*int*/);
};

class StmtJump: public Statement
{
public:
    StmtJump();
    ~StmtJump();
};

class StmtBreak: public StmtJump
{
public:
    StmtBreak();
    ~StmtBreak();

    void StmtPrint(ostream &out/*, /*int*/);
};

class StmtContinue: public StmtJump
{
public:
    StmtContinue();
    ~StmtContinue();

    void StmtPrint(ostream &out/*, int*/);
};

class StmtReturn: public StmtJump
{
private:
    SyntaxNode* arg;

public:
    StmtReturn(SyntaxNode*);
    ~StmtReturn();

    void StmtPrint(ostream &out/*, /*int*/);
};

#endif _STATEMENT_H