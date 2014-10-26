#pragma once

#include "symbol.h"

extern AsmArgMemory* real4;
extern AsmArgMemory* real8;

// for simple parser ----------------------------------------------------------
class Node
{
private:
    Node* left;
    Node* right;
    BaseToken* token;

public:
    friend class SimpleParser;
    Node(Node*, Node*, BaseToken*);
    ~Node();
};

//-----------------------------------------------------------------------------
class SyntaxNode
{
protected:
    BaseToken* token;
    int id;

public:
    friend class Parser;
    friend class NodeArr;
    friend class NodeCall;
    friend class NodeBinaryOp;
    friend class NodePrintf;
    friend class NodeDummy;
    friend SyntaxNode* MakeConversion(SyntaxNode* n, SymType* l, SymType* r);

    SyntaxNode(int, BaseToken*);
    ~SyntaxNode();

    virtual SymType* GetType();

    virtual bool IsLvalue();
    virtual bool IsModifiableLvalue();

    virtual void Print(int, int, ostream&);
    virtual void Generate(AsmCode&);
    virtual void GenerateData(AsmCode&);
    virtual void GenerateLvalue(AsmCode&);
    virtual void FPUGenerate(AsmCode&);

    void Error(int, int, const string);
    void Expected(int, int, bool, const string);
};

//-----------------------------------------------------------------------------
class NodeBinaryOp: public SyntaxNode
{
private:
    SyntaxNode* left;
    SyntaxNode* right;

public:
    friend class SyntaxNode;
    NodeBinaryOp(int, SyntaxNode*, BaseToken*, SyntaxNode*);
    NodeBinaryOp(NodeBinaryOp*);
    ~NodeBinaryOp();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);
    void Generate(AsmCode&);
    void GenerateLvalue(AsmCode&);
    void FPUGenerate(AsmCode&);
    void GenerateWithFPU(AsmCode&);
};

//-----------------------------------------------------------------------------
class NodeUnaryOp: public SyntaxNode
{
protected:
    SyntaxNode* arg;

public:
    NodeUnaryOp(int, BaseToken*, SyntaxNode*);
    NodeUnaryOp(NodeUnaryOp*);
    ~NodeUnaryOp();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);
    void Generate(AsmCode&);
    void GenerateLvalue(AsmCode&);
    void FPUGenerate(AsmCode&);
};

//-----------------------------------------------------------------------------
class NodeCall: public SyntaxNode
{
protected:
    SymTypeFunc* type;
    SyntaxNode* name;
    vector <SyntaxNode*> args;

public:
    NodeCall(int, SymTypeFunc*, SyntaxNode*);
    ~NodeCall();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void AddArg(SyntaxNode*);
    void Print(int, int, ostream&);
    void Generate(AsmCode&);
};

//-----------------------------------------------------------------------------
class NodeArr: public SyntaxNode
{
private:
    SymType* type;
    SyntaxNode* name;
    SyntaxNode* index;

public:
    NodeArr(int, SymType*, SyntaxNode*, SyntaxNode*);
    NodeArr(BaseToken*);
    ~NodeArr();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);
    void Generate(AsmCode&);
    void GenerateLvalue(AsmCode&);
};

//-----------------------------------------------------------------------------
class NodeVar: public SyntaxNode
{
private:
    Symbol* symbol;

public:
    friend class NodeBinaryOp;
    NodeVar(int, Symbol*);
    ~NodeVar();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);

    void Generate(AsmCode&);
    void GenerateData(AsmCode&);
    void GenerateLvalue(AsmCode&);
    void FPUGenerate(AsmCode&);
};

//-----------------------------------------------------------------------------
class NodePrintf: public NodeCall
{
private:
    SyntaxNode* format;

public:
    NodePrintf(int, BaseToken*, SyntaxNode*);
    ~NodePrintf();

    void Generate(AsmCode&);

    void Print(int, int, ostream&);
};
//-----------------------------------------------------------------------------
class NodeDummy: public NodeUnaryOp
{
private:
    SymType* type;

public:
    NodeDummy(SymType*, SyntaxNode*);
    ~NodeDummy();

    SymType* GetType();

    void Print(int, int, ostream&);
    void Generate(AsmCode&);
    void FPUGenerate(AsmCode&);
};
