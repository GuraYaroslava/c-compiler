#pragma once

#include <vector>
#include "token.h"

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
    SyntaxNode(BaseToken*);
    ~SyntaxNode();

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
    ~NodeUnaryOp();

    void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeCall: public SyntaxNode
{
private:
    vector<SyntaxNode*> args;

public:
    NodeCall(BaseToken*);
    ~NodeCall();

    void AddArg(SyntaxNode*);
    virtual void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeArr: public SyntaxNode
{
private:
    SyntaxNode* index;

public:
    NodeArr(BaseToken*, SyntaxNode*);
    NodeArr(BaseToken*);
    ~NodeArr();

    virtual void Print(int, int, ostream&);
};

//-----------------------------------------------------------------------------
class NodeVar: public SyntaxNode
{
public:
    NodeVar(BaseToken*);
    ~NodeVar();

    virtual void Print(int, int, ostream&);
};