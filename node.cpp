#include "node.h"

// for simple parser ----------------------------------------------------------
Node::Node(Node* left_, Node* right_, BaseToken* oper_)
{
    left = left_;
    right = right_;
    token = new BaseToken(oper_);
}

Node::~Node() {}

//-----------------------------------------------------------------------------
SyntaxNode::SyntaxNode(BaseToken* token_): token(token_) {}

SyntaxNode::~SyntaxNode() {}

void SyntaxNode::Print(int width, int indent, ostream& out)
{
    out << setw(indent);
    out << token->GetText();
    if (dynamic_cast<NodeBinaryOp*>(this))
    {
        out << (dynamic_cast<NodeBinaryOp*>(this)->left && dynamic_cast<NodeBinaryOp*>(this)->right ? " <" : "");
    }
    out << endl;
}

//-----------------------------------------------------------------------------
NodeBinaryOp::NodeBinaryOp(SyntaxNode* left_, BaseToken* oper_, SyntaxNode* right_):
    SyntaxNode(oper_)
{
    left = left_;
    right = right_;
}

NodeBinaryOp::NodeBinaryOp(NodeBinaryOp* node):
    SyntaxNode(node->token)
{
    left = node->left;
    right = node->right;
}

NodeBinaryOp::~NodeBinaryOp() {}

void NodeBinaryOp::Print(int width, int indent, ostream &out)
{
    if (left) left->Print(width, indent+width, out);
    SyntaxNode::Print(width, indent, out);
    if (right) right->Print(width, indent+width, out);
}

//-----------------------------------------------------------------------------
NodeUnaryOp::NodeUnaryOp(BaseToken* oper_, SyntaxNode* arg_):
    SyntaxNode(oper_)
{
    arg = arg_;
}

NodeUnaryOp::NodeUnaryOp(NodeUnaryOp* node):
    SyntaxNode(node->token)
{
    arg = node->arg;
}

void NodeUnaryOp::Print(int width, int indent, ostream& out)
{
    arg->Print(width, indent+width, out);
    SyntaxNode::Print(width, indent, out);
}

NodeUnaryOp::~NodeUnaryOp() {}

//-----------------------------------------------------------------------------
NodeCall::NodeCall(SyntaxNode* name_):
    SyntaxNode(NULL), name(name_), args(NULL) {}

NodeCall::~NodeCall() {}

void NodeCall::AddArg(SyntaxNode* arg_)
{
    args.push_back(arg_);
}

void NodeCall::Print(int width, int indent, ostream& out)
{
    out << setw(indent) << "funtion: " << endl;
    name->Print(width, indent+width, out);

    if (args.size() > 0)
    {
        out << setw(indent) << "args: " << endl;
    }
    for (int i = 0, size = args.size(); i < size; ++i)
    {
        args[i]->Print(width, indent+width, out);
    }
    out << endl;
}

//-----------------------------------------------------------------------------
NodeArr::NodeArr(SyntaxNode* name_, SyntaxNode* index_):
    SyntaxNode(NULL), name(name_), index(index_) {}

NodeArr::~NodeArr() {}

void NodeArr::Print(int width, int indent, ostream& out)
{
    out << setw(indent) << "array: " << endl;
    name->Print(width, indent+width, out);
    out << setw(indent) << "index: " << endl;
    index->Print(width, indent+width, out);
}

//-----------------------------------------------------------------------------
NodeVar::NodeVar(BaseToken* token): SyntaxNode(token) {}

NodeVar::~NodeVar() {}

void NodeVar::Print(int width, int indent, ostream& out)
{
    SyntaxNode::Print(width, indent, out);
}