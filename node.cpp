#include "node.h"
#include "symbol.h"
#include "exception.h"
//typedef vector<SyntaxNode*>::iterator SyntaxNodeIter;

//for simple parser -----------------------------------------------------------
Node::Node(Node* left_, Node* right_, BaseToken* token_)
{
    left = left_;
    right = right_;
    token = new BaseToken(token_);
}

Node::~Node() 
{
    delete token;
    token = NULL;
}

//-----------------------------------------------------------------------------
SyntaxNode::SyntaxNode(BaseToken* token_): token(token_) {}

SyntaxNode::~SyntaxNode()
{
    delete token;
    token = NULL;
}

void SyntaxNode::Print(int width, int indent, ostream &out)
{
    if (token == NULL) return;
    out << setw(indent);
    if (token->GetType()  == ROUND_LEFT_BRACKET)
        out << "()" << endl;    
    else if (token->GetType() == SQUARE_LEFT_BRACKET)
        out << "[]" << endl;
    else out << token->GetText() << endl;
}

SymType* SyntaxNode::GetType()
{ 
    return NULL;
}

//-----------------------------------------------------------------------------
NodeBinaryOp::NodeBinaryOp(): SyntaxNode(NULL), left(NULL), right(NULL) {}

NodeBinaryOp::NodeBinaryOp(SyntaxNode* left_, BaseToken* token_, SyntaxNode* right_):
SyntaxNode(token_)
{
    left = left_;
    right = right_;
}

NodeBinaryOp::NodeBinaryOp(NodeBinaryOp *_NodeBinaryOp):
SyntaxNode(_NodeBinaryOp->token)
{
    left = _NodeBinaryOp->left;
    right = _NodeBinaryOp->right;
}

NodeBinaryOp::~NodeBinaryOp() 
{
    delete left;
    delete right;
    left = NULL;
    right = NULL;
}

void NodeBinaryOp::Print(int width, int indent, ostream &out)
{
    if (left) left->Print(width, indent+width, out);
    SyntaxNode::Print(width, indent, out);
    if (right) right->Print(width, indent+width, out);
}

SymType* NodeBinaryOp::GetType()
{
    SymType* t_left = left->GetType();
    SymType* t_right = right->GetType();
    SymType* response = NULL;
    //cout << t_left->type->GetText() << endl << endl << t_right->type->GetText() << endl << endl;
    if (*token == BIT_AND || *token == BIT_NOT || *token == BIT_OR || *token == BIT_XOR ||
        *token == BIT_SHIFT_LEFT || *token == BIT_SHIFT_RIGHT || *token == MODULO)
    {
        if (*t_left->type != INT || *t_right->type != INT)
            throw Exception(0, 0, "Requires an expression of type integer.");
        response = t_left;
    }
    else
        if (dynamic_cast <SymTypeInteger*> (t_left) &&  dynamic_cast <SymTypeInteger*> (t_right) || 
            dynamic_cast <SymTypeChar*> (t_left) && dynamic_cast <SymTypeChar*> (t_right) || 
            dynamic_cast <SymTypeDouble*> (t_left) && dynamic_cast <SymTypeDouble*> (t_right))
            response = t_left;
        else if (dynamic_cast <SymTypeInteger*> (t_left) && dynamic_cast <SymTypeDouble*> (t_right))
            response = t_right;
        else if (dynamic_cast <SymTypeDouble*> (t_left) && dynamic_cast <SymTypeInteger*> (t_right))
            response = t_left;
        else if (dynamic_cast <SymTypeInteger*> (t_left) && dynamic_cast <SymTypeChar*> (t_right))
            response = t_left;
        else if (dynamic_cast <SymTypeChar*> (t_left) && dynamic_cast <SymTypeInteger*> (t_right))
            response = t_right;
        else if (dynamic_cast <SymTypeDouble*> (t_left) && dynamic_cast <SymTypeChar*> (t_right))
            response = t_left;
        else if (dynamic_cast <SymTypeChar*> (t_left) && dynamic_cast <SymTypeDouble*> (t_right))
            response = t_right;
    if (!response) throw Exception(0, 0, "[BinaryOp -> GetType()]");
    return response;
}

//-----------------------------------------------------------------------------
NodeRecordAccess::NodeRecordAccess(): NodeBinaryOp(NULL), symbol(NULL) {}

NodeRecordAccess::NodeRecordAccess(SyntaxNode* left_, BaseToken* token_, SyntaxNode* right_):
    NodeBinaryOp(left_, token_, right_), symbol(NULL) {}

void NodeRecordAccess::Print(int width, int indent, ostream &out)
{
    NodeBinaryOp::Print(width, indent, out);
}

SymType* NodeRecordAccess::GetType()
{
    //return symbol->type;
    /**bool f = false;
    for (int i=0; i<dynamic_cast <SymTypeRecord*> (symbol->type)->fields->symbols.size(); i++)
        if (!strcmp(&dynamic_cast <SymTypeRecord*> (symbol->type)->fields->symbols[i]->name->GetText()[0], &field->token->GetText()[0]))
        {
            f = true;
            s = dynamic_cast <SymVar*> (dynamic_cast <SymTypeRecord*> (dynamic_cast <SymVar*>(s)->type)->fields->symbols[i])->type;
        }
    if (!f) Error("Stupid. There is no such field.");*/
    return NULL;
}

//-----------------------------------------------------------------------------
NodeAssignOp::NodeAssignOp(): NodeBinaryOp(NULL) {}

NodeAssignOp::NodeAssignOp(SyntaxNode* left_, BaseToken* token_, SyntaxNode* right_):
    NodeBinaryOp(left_, token_, right_) {}

void NodeAssignOp::Print(int width, int indent, ostream &out)
{
    NodeBinaryOp::Print(width, indent, out);
}

//-----------------------------------------------------------------------------
NodeUnaryOp::NodeUnaryOp(): SyntaxNode(NULL), arg(NULL) {}

NodeUnaryOp::NodeUnaryOp(BaseToken* token_, SyntaxNode* arg_):

SyntaxNode(token)
{
    token = token_;
    arg = arg_;
}

NodeUnaryOp::NodeUnaryOp(NodeUnaryOp* _NodeUnaryOp):
SyntaxNode(token)
{
    token = _NodeUnaryOp->token;
    arg = _NodeUnaryOp->arg;
}

SymType* NodeUnaryOp::GetType()
{
    SymType* response = arg->GetType();
    //if (response->type->GetType() == CHAR)
        //response = приводим к типу int (промежуточный узел и прочее)
    if (!response || (response->type->GetType() != INT)) 
        throw Exception(0, 0, "Requires an expression of type integer.");
    return response;
}

void NodeUnaryOp::Print(int width, int indent, ostream &out)
{
    SyntaxNode::Print(width, indent, out);
    if (arg) arg->Print(width, indent+width, out);
}

NodeUnaryOp::~NodeUnaryOp() 
{
    delete token;
    delete arg;
    token = NULL;
    arg = NULL;
}

//-----------------------------------------------------------------------------
NodeCall::NodeCall(): SyntaxNode(NULL), args(NULL), symbol(NULL) {}

NodeCall::NodeCall(SyntaxNode* _name, BaseToken* _oper): SyntaxNode(_oper), args(NULL), symbol(NULL), name(_name) {}

NodeCall::~NodeCall()
{
    delete name;
    name = NULL;
    args.clear();
}

void NodeCall::AddArg(SyntaxNode* arg_)
{
    args.push_back(arg_);
}

void NodeCall::PrintArgs(int width, int indent, ostream &out)
{
    for (int i=0; i<args.size(); i++)
        args[i]->Print(width, indent, out);
    out << endl;
}

void NodeCall::Print(int width, int indent, ostream &out)
{
    out << setw(indent+width);
    name->Print(width, indent+width, out);
    out << setw(indent);
    SyntaxNode::Print(width, indent, out);
    PrintArgs(width, indent+width, out);
}

SymType* NodeCall::GetType()
{
    int i = args.size(), j = symbol->args->symbols.size();
    if (i != j) 
        throw Exception(0, 0, "Number of arguments does not match the number of parameters.");
    /*for (int i=0; i<j; i++)
    {
        SymType* t_param = symbol->args->symbols[j-1-i]->GetType();
        SymType* t_arg = args[i]->GetType();
        //cout << "///////////////////" << endl << t_param->type->GetText() << endl << endl << t_arg->type->GetText() << endl<< "///////////////////" << endl << endl;
        /*if (*t_param != t_arg )
            throw Exception(0, 0, "The type of argument does not match the type of parameter.");*/
        /*if ((dynamic_cast <SymTypeInteger*> (t_param) || dynamic_cast <SymTypeChar*> (t_param) || dynamic_cast <SymTypeDouble*> (t_param)) && 
            (dynamic_cast <SymTypeInteger*> (t_arg) || dynamic_cast <SymTypeChar*> (t_arg) || dynamic_cast <SymTypeDouble*> (t_arg)))
            continue;
        if (dynamic_cast <SymTypeRecord*> (t_param) && dynamic_cast <SymTypeRecord*> (t_arg))
        {

        }
            
    throw Exception(0, 0, "The type of argument does not match the type of parameter.");
    }*/
    return symbol->type;
}

//-----------------------------------------------------------------------------
NodeVar::NodeVar(BaseToken* token_): SyntaxNode(token_), symbol(NULL) {}

NodeVar::NodeVar(): SyntaxNode(NULL), symbol(NULL) {}

NodeVar::~NodeVar()
{
    delete token;
    token = NULL;
}

void NodeVar::Print(int width, int indent, ostream &out)
{
    SyntaxNode::Print(width, indent, out);
}

SymType* NodeVar::GetType()
{
    return symbol->GetType();
}
