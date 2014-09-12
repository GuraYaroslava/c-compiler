#pragma once

#include "symbol.h"

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

public:
    friend class Parser;
    friend class NodeCall;
    friend class NodeBinaryOp;
    friend SyntaxNode* MakeConversion(SyntaxNode* n, SymType* l, SymType* r);

    SyntaxNode(BaseToken*);
    ~SyntaxNode();

    virtual SymType* GetType();

    virtual bool IsLvalue();
    virtual bool IsModifiableLvalue();

    virtual void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeBinaryOp: public SyntaxNode
{
private:
    SyntaxNode* left;
    SyntaxNode* right;

public:
    friend class SyntaxNode;
    NodeBinaryOp(SyntaxNode*, BaseToken*, SyntaxNode*);
    NodeBinaryOp(NodeBinaryOp*);
    ~NodeBinaryOp();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeUnaryOp: public SyntaxNode
{
private:
    SyntaxNode* arg;

public:
    NodeUnaryOp(BaseToken*, SyntaxNode*);
    NodeUnaryOp(NodeUnaryOp*);
    ~NodeUnaryOp();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeCall: public SyntaxNode
{
private:
    SymTypeFunc* type;
    SyntaxNode* name;
    vector <SyntaxNode*> args;

public:
    NodeCall(SymTypeFunc*, SyntaxNode*);
    ~NodeCall();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void AddArg(SyntaxNode*);
    void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeArr: public SyntaxNode
{
private:
    SyntaxNode* name;
    SyntaxNode* index;

public:
    NodeArr(SyntaxNode*, SyntaxNode*);
    NodeArr(BaseToken*);
    ~NodeArr();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

    void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeVar: public SyntaxNode
{
private:
    Symbol* symbol;

public:
    NodeVar(Symbol*);
    ~NodeVar();

    SymType* GetType();

    bool IsLvalue();
    bool IsModifiableLvalue();

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

    //bool IsLvalue();
    //bool IsModifiableLvalue();

    void Print(int, int, ostream&);
};
