#pragma once

#include <vector>
//#include "symbol.h"
#include "token.h"

class Parser;
class Symbol;
class SymType;
class SymFunc;
class SymVar;

class Node
{
public:
    Node* left;
    Node* right;
    BaseToken* token;

    Node(Node*, Node*, BaseToken*);
    ~Node();
};

//-----------------------------------------------------------------------------
class SyntaxNode
{
public:
    BaseToken* token;

public:
    SyntaxNode(BaseToken*);
    ~SyntaxNode();

    virtual void Print(int, int, ostream&);
    virtual SymType* GetType();
};

//-----------------------------------------------------------------------------
class NodeBinaryOp: public SyntaxNode
{
private:
    SyntaxNode* left;
    SyntaxNode* right;

public:
    NodeBinaryOp();
    NodeBinaryOp(SyntaxNode*, BaseToken*, SyntaxNode*);
    NodeBinaryOp(NodeBinaryOp*);
    ~NodeBinaryOp();

    virtual void Print(int, int, ostream&);
    virtual SymType* GetType();
};

//-----------------------------------------------------------------------------
class NodeRecordAccess: public NodeBinaryOp
{
private:
    SymVar *symbol;

public:
    NodeRecordAccess();
    NodeRecordAccess(SyntaxNode*, BaseToken*, SyntaxNode*);
    ~NodeRecordAccess();

    virtual void Print(int, int, ostream&);
    SymType* GetType();
    friend Parser;
};

//-----------------------------------------------------------------------------
class NodeAssignOp: public NodeBinaryOp
{
public:
    NodeAssignOp();
    NodeAssignOp(SyntaxNode*, BaseToken*, SyntaxNode*);
    ~NodeAssignOp();

    virtual void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeUnaryOp: public SyntaxNode
{
private:
    SyntaxNode* arg;

public:
    NodeUnaryOp(BaseToken*, SyntaxNode*);
    NodeUnaryOp(NodeUnaryOp*);
    NodeUnaryOp();
    ~NodeUnaryOp();

    void Print(int, int, ostream&);
    SymType* GetType();
};

//-----------------------------------------------------------------------------
class NodeCall: public SyntaxNode  
{
private:
    SymFunc* symbol;
    SyntaxNode* name;
    vector<SyntaxNode*> args;

public:
    NodeCall(SyntaxNode*, BaseToken*);
    NodeCall();
    ~NodeCall();

    void AddArg(SyntaxNode*);
    void PrintArgs(int, int, ostream&);
    virtual void Print(int, int, ostream&);
    SymType* GetType();
    friend Parser;
};

//-----------------------------------------------------------------------------
class NodeVar: public SyntaxNode
{
private:
    Symbol* symbol;

public:
    NodeVar(BaseToken*);
    NodeVar();
    ~NodeVar();

    virtual void Print(int, int, ostream&);
    SymType* GetType();
    friend Parser;
};