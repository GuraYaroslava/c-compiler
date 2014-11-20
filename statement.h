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

    void Print(int, ostream&);
    void Generate(AsmCode&);
    void SetUnUsed(BaseParser&);
    Statement* Optimize(bool&, BaseParser&);
    float Calculate();
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

    void SetUnUsed(BaseParser&);
    void AddStatement(Statement*);
    void Print(int, ostream&);
    void Generate(AsmCode&);
    void Delete(int);
    Statement* Optimize(bool&, BaseParser&);

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

    void SetUnUsed(BaseParser&);
    void Print(int, ostream&);
    void Generate(AsmCode&);
    Statement* Optimize(bool&, BaseParser&);
    Statement* DeadCodeEliminate(bool&, BaseParser&);
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
    SyntaxNode* expr1;
    SyntaxNode* expr2;
    SyntaxNode* expr3;

public:
    StmtFor(SyntaxNode*, SyntaxNode*, SyntaxNode*);
    ~StmtFor();

    void SetUnUsed(BaseParser&);
    void Print(int, ostream&);
    void Generate(AsmCode&);
    Statement* Optimize(bool&, BaseParser&);
};

//-----------------------------------------------------------------------------
class StmtWhile: public StmtIteration
{
private:
    SyntaxNode* condition;

public:
    StmtWhile(SyntaxNode*);
    ~StmtWhile();

    void SetUnUsed(BaseParser&);
    void Print(int, ostream&);
    void Generate(AsmCode&);
    Statement* Optimize(bool&, BaseParser&);
};

//-----------------------------------------------------------------------------
class StmtJump: public Statement
{
protected:
    Statement* owner;

public:
    StmtJump(Statement*);
    ~StmtJump();
};

//-----------------------------------------------------------------------------
class StmtBreak: public StmtJump
{
public:
    StmtBreak(Statement*);
    ~StmtBreak();

    void Print(int, ostream&);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class StmtContinue: public StmtJump
{
public:
    StmtContinue(Statement*);
    ~StmtContinue();

    void Print(int, ostream&);
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

    void Print(int, ostream&);
    void Generate(AsmCode&);
    Statement* Optimize(bool&, BaseParser&);
};
