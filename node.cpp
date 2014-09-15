#include "node.h"
#include "exception.h"

SymTypeScalar* intType = new SymTypeScalar(new BaseToken("int", 0, 0, KEYWORD, INT));
SymTypeScalar* floatType = new SymTypeScalar(new BaseToken("float", 0, 0, KEYWORD, FLOAT));
SymTypeScalar* charType = new SymTypeScalar(new BaseToken("char", 0, 0, KEYWORD, CHAR));
SymTypePointer* stringType = new SymTypePointer(charType);

SymType* GetWideType(SymType*, SymType*);
bool IsIntegralType(SymType*);

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

SymType* SyntaxNode::GetType()
{
    return NULL;
}

bool SyntaxNode::IsLvalue()
{
    return false;
}

bool SyntaxNode::IsModifiableLvalue()
{
    return false;
}

void SyntaxNode::Print(int width, int indent, ostream& out)
{
    if (!token)
    {
        return;
    }
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

bool NodeBinaryOp::IsLvalue()
{
    switch (token->GetSubType())
    {
    case POINT:
    case ARROW:
        return right->IsLvalue();

    default:
        return IsModifiableLvalue();
    }
}

bool NodeBinaryOp::IsModifiableLvalue()
{
    switch (token->GetSubType())
    {
    case ASSIGN:
    case ADD_ASSIGN:
    case SUB_ASSIGN:
    case MUL_ASSIGN:
    case DIV_ASSIGN:
    case MOD_ASSIGN:
    case BIT_XOR_ASSIGN:
    case BIT_AND_ASSIGN:
    case BIT_OR_ASSIGN:
    case BIT_SHIFT_LEFT_ASSIGN:
    case BIT_SHIFT_RIGHT_ASSIGN:
        return left->IsModifiableLvalue();

    case POINT:
    case ARROW:
        return right->IsModifiableLvalue();

    default:
        return false;
    }
}

SymType* NodeBinaryOp::GetType()
{
    SymType* leftType = left->GetType();
    SymType* rightType = right->GetType();

    SymType* wideType = GetWideType(leftType, rightType);

    SymTypePointer* leftTypePointer = dynamic_cast<SymTypePointer*>(leftType);
    SymTypePointer* rightTypePointer = dynamic_cast<SymTypePointer*>(rightType);

    SymTypeArray* leftTypeArray = dynamic_cast<SymTypeArray*>(leftType);
    SymTypeArray* rightTypeArray = dynamic_cast<SymTypeArray*>(rightType);

    switch (token->GetSubType())
    {
    case BIT_AND_ASSIGN:

    case BIT_XOR_ASSIGN:

    case BIT_OR_ASSIGN:

    case BIT_SHIFT_LEFT_ASSIGN:

    case BIT_SHIFT_RIGHT_ASSIGN:

    case MOD_ASSIGN:
        if (!leftType->CanConvertTo(intType) || !rightType->CanConvertTo(intType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must have integral type");
        }

    case ASSIGN:
        if (dynamic_cast<SymTypeStruct*>(leftType) && leftType == rightType)
        {
            return leftType;
        }

    case MUL_ASSIGN:

    case ADD_ASSIGN:

    case SUB_ASSIGN:

    case DIV_ASSIGN:
        if (!left->IsModifiableLvalue())
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must be a modifiable lvalue");
        }

        right = MakeConversion(right, rightType, leftType);
        return leftType;

    case POINT:
        if (!dynamic_cast<SymTypeStruct*>(leftType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must have struct type");
        }
        return rightType;

    case ARROW:
        if (!leftTypePointer
            || !dynamic_cast<SymTypeStruct*>(leftTypePointer->refType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must have pointer-to-struct type");
        }
        return rightType;

    case SUBSTRACTION:
        if (leftTypePointer && rightTypePointer)
        {
            if (leftTypePointer->refType != rightTypePointer->refType)
            {
                throw Exception(token->GetLine(),
                                token->GetPosition(),
                                "operand types are incompatible");
            }
            return intType;
        }

        if (leftTypePointer || rightTypePointer)
        {
            if (leftTypePointer && (IsIntegralType(rightType) || rightType->CanConvertTo(leftType))
                || rightTypePointer && (IsIntegralType(leftType) || leftType->CanConvertTo(rightType)))
            {
                return intType;
            }
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "operand types are incompatible");
        }

    case ADDITION:
        if (leftTypePointer && rightTypePointer || leftTypeArray && rightTypeArray)
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must have integral type");
        }

        if (leftTypePointer && (IsIntegralType(rightType)/* || leftType == rightType*/)
            || rightTypePointer && (IsIntegralType(leftType)/* || leftType == rightType*/))
        {
            return leftTypePointer == 0 ? rightType : leftType;
        }
        
        if (leftTypeArray && rightType->CanConvertTo(intType)
            || rightTypeArray && leftType->CanConvertTo(intType))
        {
            return new SymTypePointer(leftTypeArray == 0 ? rightTypeArray->type : leftTypeArray->type);
        }

        //{
        //    throw Exception(token->GetLine(),
        //                    token->GetPosition(),
        //                    "expression must have integral type");
        //}

    default:
        if (dynamic_cast<SymTypeStruct*>(leftType) || dynamic_cast<SymTypeStruct*>(rightType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "no operator matches these operands (struct)");
        }

        left = MakeConversion(left, leftType, wideType);
        right = MakeConversion(right, rightType, wideType);

        return wideType;
    }
}

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

NodeUnaryOp::~NodeUnaryOp() {}

SymType* NodeUnaryOp::GetType()
{
    SymType* type = arg->GetType();

    switch (token->GetSubType())
    {
    case MULTIPLICATION: // Indirection Operator
        if (!dynamic_cast<SymTypePointer*>(type))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "operad of `*` must be a pointer");
        }
        return dynamic_cast<SymTypePointer*>(type)->refType;

    case BIT_AND: // Address Operator
        if (!arg->IsLvalue())
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must be an lvalue or a function designator");
        }
        return new SymTypePointer(type);

    case BIT_NOT:
        if (!type->CanConvertTo(intType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must have integral type");
        }
        arg = MakeConversion(arg, type, intType);
        break;

    case NOT:
        if (!dynamic_cast<SymTypePointer*>(type)
            && !dynamic_cast<SymTypeArray*>(type)
            && !type->CanConvertTo(floatType)
            && !type->CanConvertTo(intType)
            && !type->CanConvertTo(charType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "expression must have integral type");
        }
        break;

    case ADDITION:
    case SUBSTRACTION:
        if (!type->CanConvertTo(floatType))
        {
            throw Exception(token->GetLine(),
                            token->GetPosition(),
                            "exspression must have arithmetic type");
        }
    }

    return type;
}

bool NodeUnaryOp::IsModifiableLvalue()
{
    SymType* type = GetType();
    return *token == MULTIPLICATION && type->IsModifiableLvalue();
}

bool NodeUnaryOp::IsLvalue()
{
    return *token == MULTIPLICATION;
}

void NodeUnaryOp::Print(int width, int indent, ostream& out)
{
    arg->Print(width, indent+width, out);
    SyntaxNode::Print(width, indent, out);
}

//-----------------------------------------------------------------------------
NodeCall::NodeCall(SymTypeFunc* type_, SyntaxNode* name_):
    SyntaxNode(name_->token),
    type(type_),
    name(name_),
    args(NULL)
    {}

NodeCall::~NodeCall() {}

SymType* NodeCall::GetType()
{
    int formalParametersCount = type->params->GetSize();
    int realParametersCount = args.size();

    if (formalParametersCount != realParametersCount)
    {
        throw Exception(name->token->GetLine(),
                        name->token->GetPosition(),
                        "incorrect arguments in function call");
    }

    for (int i = 0; i < formalParametersCount; ++i)
    {
        SymType* realParamType = args[i]->GetType();
        SymType* formalParamType = type->params->symbols[i]->GetType();

        if (!realParamType->CanConvertTo(formalParamType))
        {
            throw Exception(args[i]->token->GetLine(),
                            args[i]->token->GetPosition(),
                            "argument is incompatible with parameter");
        }

        args[i] = MakeConversion(args[i], realParamType, formalParamType);
    }

    return type->type;
}

void NodeCall::AddArg(SyntaxNode* arg_)
{
    args.push_back(arg_);
}

bool NodeCall::IsModifiableLvalue()
{
    return false;
}

bool NodeCall::IsLvalue()
{
    return false;
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

SymType* NodeArr::GetType()
{
    SymType* type = name->GetType();
    if (!dynamic_cast<SymTypeArray*>(type)
        && !dynamic_cast<SymTypePointer*>(type))
    {
        throw Exception(token->GetLine(),
                        token->GetPosition(),
                        "expression must be a pointer to a complete object type");
    }
    SymTypeArray* arrType = dynamic_cast<SymTypeArray*>(type);
    SymTypePointer* pType = dynamic_cast<SymTypePointer*>(type);
    return arrType ? arrType->type : pType->refType;
}

bool NodeArr::IsModifiableLvalue()
{
    SymType* type = name->GetType();
    return type->IsModifiableLvalue();
}

bool NodeArr::IsLvalue()
{
    return true;
}

void NodeArr::Print(int width, int indent, ostream& out)
{
    out << setw(indent) << "array: " << endl;
    name->Print(width, indent+width, out);
    out << setw(indent) << "index: " << endl;
    index->Print(width, indent+width, out);
}

//-----------------------------------------------------------------------------
NodeVar::NodeVar(Symbol* symbol_):
    SyntaxNode(symbol_->name),
    symbol(symbol_)
    {}

NodeVar::~NodeVar() {}

SymType* NodeVar::GetType()
{
    return symbol->GetType();
}

bool NodeVar::IsLvalue()
{
    Symbol* type = symbol->GetType();
    if (!dynamic_cast<SymTypeScalar*>(type))
    {
        throw Exception(token->GetLine(),
                        token->GetPosition(),
                        "NODE VAR HAVE NOT SCALAR TYPE");
    }

    if (type->name->GetSubType() == IDENTIFIER)
    {
        return true;
    }

    return false;
}

bool NodeVar::IsModifiableLvalue()
{
    Symbol* type = symbol->GetType();
    SymTypeScalar* sc = dynamic_cast<SymTypeScalar*>(type);

    if (sc && *symbol->name == IDENTIFIER)
    {
        return true;
    }

    if (dynamic_cast<SymTypePointer*>(type))
    {
        return true;
    }

    return false;
}

void NodeVar::Print(int width, int indent, ostream& out)
{
    SyntaxNode::Print(width, indent, out);
}

//-----------------------------------------------------------------------------
NodeDummy::NodeDummy(SymType* type_, SyntaxNode* node):
    NodeUnaryOp(NULL, node),
    type(type_)
    {}

NodeDummy::~NodeDummy() {}

SymType* NodeDummy::GetType()
{
    return type;
}

void NodeDummy::Print(int width, int indent, ostream& out)
{
    NodeUnaryOp::Print(width, indent, out);
}

//-----------------------------------------------------------------------------
SymType* GetWideType(SymType* left, SymType* right)
{
    if (dynamic_cast<SymTypeScalar*>(left) && dynamic_cast<SymTypeScalar*>(right))
    {
        return left->name->GetSubType() >= right->name->GetSubType() ? left : right;
    }
    return NULL;
}

SyntaxNode* MakeConversion(SyntaxNode* node, SymType* from, SymType* to)
{
    if (!from->CanConvertTo(to))
    {
        throw Exception(node->token->GetLine(),
                        node->token->GetPosition(),
                        "invalid conversion");
                        //"expression must be a pointer to a complete object type"
                        //"expression must have integral type"
    }

    return new NodeDummy(to, node);
}

bool IsIntegralType(SymType* type)
{
    if (type == intType || type == charType)
    {
        return true;
    }
    return false;
}
