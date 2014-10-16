#pragma once

#include "node.h"
#include "statement_base.h"

using namespace std;

//-----------------------------------------------------------------------------
class StmtExpr: public Statement
{
private:
    SyntaxNode* expr;

public:
    StmtExpr(SyntaxNode*);
    ~StmtExpr();

    void StmtPrint(ostream&, int);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class SymTable;

class StmtBlock: public Statement
{
private:
    SymTable* locals;
    vector <Statement*> statements;

public:
    StmtBlock();
    ~StmtBlock();

    void AddStatement(Statement*);
    void StmtPrint(ostream&, int);
    void Generate(AsmCode&);
    friend class Parser;
};

//-----------------------------------------------------------------------------
class StmtIf: public Statement
{
private:
    SyntaxNode* condition;
    Statement* bodyIf;
    Statement* bodyElse;

public:
    StmtIf(SyntaxNode*,  Statement*, Statement*);
    ~StmtIf();

    void StmtPrint(ostream&, int);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class StmtIteration: public Statement
{
protected:
    AsmArgLabel* start;
    AsmArgLabel* inc;
    AsmArgLabel* cond;
    AsmArgLabel* end;
    Statement* body;

public:
    StmtIteration();
    ~StmtIteration();

    virtual void SetStartLabel(string);
    virtual void SetIncLabel(string);
    virtual void SetCondLabel(string);
    virtual void SetEndLabel(string);
    virtual void SetBody(Statement*);

    friend class StmtContinue;
    friend class StmtBreak;
};

//-----------------------------------------------------------------------------
class StmtFor: public StmtIteration
{
private:
    StmtExpr *expr1;
    StmtExpr *expr2;
    StmtExpr *expr3;

public:
    StmtFor(SyntaxNode*, SyntaxNode*, SyntaxNode*);
    ~StmtFor();

    void StmtPrint(ostream&, int);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class StmtWhile: public StmtIteration
{
private:
    SyntaxNode* condition;

public:
    StmtWhile(SyntaxNode*);
    ~StmtWhile();

    void StmtPrint(ostream&, int);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class StmtJump: public Statement
{
public:
    StmtJump();
    ~StmtJump();
};

//-----------------------------------------------------------------------------
class StmtBreak: public StmtJump
{
public:
    StmtBreak();
    ~StmtBreak();

    void StmtPrint(ostream& out, int);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class StmtContinue: public StmtJump
{
public:
    StmtContinue();
    ~StmtContinue();

    void StmtPrint(ostream& out, int);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class StmtReturn: public StmtJump
{
private:
    SyntaxNode* arg;
    SymTypeFunc* func;

public:
    StmtReturn(SyntaxNode*, SymTypeFunc*);
    ~StmtReturn();

    void StmtPrint(ostream& out, int);
    void Generate(AsmCode&);
};
