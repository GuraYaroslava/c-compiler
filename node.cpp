#include "node.h"
#include "exception.h"

class Parser;

SymTypeScalar* intType = new SymTypeScalar(new BaseToken("int", 0, 0, KEYWORD, INT));
SymTypeScalar* floatType = new SymTypeScalar(new BaseToken("float", 0, 0, KEYWORD, FLOAT));
SymTypeScalar* charType = new SymTypeScalar(new BaseToken("char", 0, 0, KEYWORD, CHAR));
SymTypePointer* stringType = new SymTypePointer(charType);

static bool IsIntegralType(SymType*);
static SymType* GetWideType(SymType*, SymType*);

// for simple parser ----------------------------------------------------------
Node::Node(Node* left_, Node* right_, BaseToken* oper_)
{
    left = left_;
    right = right_;
    token = new BaseToken(oper_);
}

Node::~Node() {}

//-----------------------------------------------------------------------------
SyntaxNode::SyntaxNode(int id_, BaseToken* token_): id(id_), token(token_) {}

SyntaxNode::~SyntaxNode() {}

SymType* SyntaxNode::GetType()
{
    return NULL;
}

bool SyntaxNode::IsConstant()
{
    return false;
}

bool SyntaxNode::IsLvalue()
{
    return false;
}

bool SyntaxNode::IsModifiableLvalue()
{
    return false;
}

void SyntaxNode::Error(int ln, int col, const string msg)
{
    throw Exception(ln, col, msg);
}

void SyntaxNode::Expected(int ln, int col, bool actual, const string msg)
{
    bool expected = true;
    if (actual != expected)
    {
        Error(ln, col, msg);
    }
}

void SyntaxNode::SetUnUsed(BaseParser&)
{

}

//-----------------------------------------------------------------------------
NodeBinaryOp::NodeBinaryOp(int id_, SyntaxNode* left_, BaseToken* oper_, SyntaxNode* right_):
    SyntaxNode(id_, oper_)
{
    left = left_;
    right = right_;
}

NodeBinaryOp::NodeBinaryOp(NodeBinaryOp* node):
    SyntaxNode(node->id, node->token)
{
    left = node->left;
    right = node->right;
}

NodeBinaryOp::~NodeBinaryOp() {}

void NodeBinaryOp::SetUnUsed(BaseParser& parser)
{
    left->SetUnUsed(parser);
    right->SetUnUsed(parser);
}

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
        Expected(token->GetLine(), token->GetPosition(),
                 leftType->CanConvertTo(intType) && rightType->CanConvertTo(intType),
                 "expression must have integral type");

    case ASSIGN:
        if (*leftType == rightType)
        {
            return leftType;
        }

    case MUL_ASSIGN:
    case ADD_ASSIGN:
    case SUB_ASSIGN:
    case DIV_ASSIGN:
        Expected(token->GetLine(), token->GetPosition(),
                 left->IsModifiableLvalue(),
                 "expression must be a modifiable lvalue");

        right = MakeConversion(right, rightType, leftType);
        return leftType;

    case POINT:
        Expected(token->GetLine(), token->GetPosition(),
                 dynamic_cast<SymTypeStruct*>(leftType),
                 "expression must have struct type");
        return rightType;

    case ARROW:
        Expected(token->GetLine(), token->GetPosition(),
                 leftTypePointer && dynamic_cast<SymTypeStruct*>(leftTypePointer->refType),
                 "expression must have pointer-to-struct type");
        return rightType;

    case SUBSTRACTION:
        if (leftTypePointer && rightTypePointer)
        {
            Expected(token->GetLine(), token->GetPosition(),
                     leftTypePointer->refType == rightTypePointer->refType,
                     "operand types are incompatible");
            return intType;
        }

        //if (leftTypePointer || rightTypePointer)
        //{
        //    Expected(token->GetLine(), token->GetPosition(),
        //             leftTypePointer && (IsIntegralType(rightType) || rightType->CanConvertTo(leftType))
        //             || rightTypePointer && (IsIntegralType(leftType) || leftType->CanConvertTo(rightType)),
        //             "operand types are incompatible");
        //    return intType;
        //}

    case ADDITION:
        Expected(token->GetLine(), token->GetPosition(),
            (!leftTypePointer || !rightTypePointer) && (!leftTypeArray || !rightTypeArray),
            "expression must have integral type");

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
        Expected(token->GetLine(), token->GetPosition(),
            !dynamic_cast<SymTypeStruct*>(leftType) && !dynamic_cast<SymTypeStruct*>(rightType),
            "no operator matches these operands (struct)");

        left = MakeConversion(left, leftType, wideType);
        right = MakeConversion(right, rightType, wideType);

        return wideType;
    }
}

//-----------------------------------------------------------------------------
NodeUnaryOp::NodeUnaryOp(int id_, BaseToken* oper_, SyntaxNode* arg_):
    SyntaxNode(id_, oper_)
{
    arg = arg_;
}

NodeUnaryOp::NodeUnaryOp(NodeUnaryOp* node):
    SyntaxNode(node->id, node->token)
{
    arg = node->arg;
}

NodeUnaryOp::~NodeUnaryOp() {}

void NodeUnaryOp::SetUnUsed(BaseParser& parser)
{
    arg->SetUnUsed(parser);
}

SymType* NodeUnaryOp::GetType()
{
    SymType* type = arg->GetType();

    switch (token->GetSubType())
    {
    case MULTIPLICATION: // Indirection Operator
        Expected(token->GetLine(), token->GetPosition(),
            dynamic_cast<SymTypePointer*>(type), "operad of `*` must be a pointer");
        return dynamic_cast<SymTypePointer*>(type)->refType;

    case BIT_AND: // Address Operator
        Expected(token->GetLine(), token->GetPosition(),
            arg->IsLvalue(), "expression must be an lvalue or a function designator");
        return new SymTypePointer(type);

    case BIT_NOT:
        Expected(token->GetLine(), token->GetPosition(),
            type->CanConvertTo(intType), "expression must have integral type");
        arg = MakeConversion(arg, type, intType);
        break;

    case NOT:
        Expected(token->GetLine(), token->GetPosition(),
                 dynamic_cast<SymTypePointer*>(type)
                 || dynamic_cast<SymTypeArray*>(type)
                 || type->CanConvertTo(floatType)
                 || type->CanConvertTo(intType)
                 || type->CanConvertTo(charType),
                 "expression must have integral type");
        break;

    case ADDITION:
    case SUBSTRACTION:
        Expected(token->GetLine(), token->GetPosition(),
                 type->CanConvertTo(floatType),
                 "exspression must have arithmetic type");
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

//-----------------------------------------------------------------------------
NodeCall::NodeCall(int id_, SymTypeFunc* type_, SyntaxNode* name_):
    SyntaxNode(id_, name_->token),
    type(type_),
    name(name_),
    args(NULL)
    {}

NodeCall::~NodeCall() {}

void NodeCall::SetUnUsed(BaseParser& parser)
{
    name->SetUnUsed(parser);
    if (args.empty()) return;
    for (int i = 0; i < args.size(); ++i)
    {
        args[i]->SetUnUsed(parser);
    }
}

SymType* NodeCall::GetType()
{
    int formalParametersCount = type->params->GetSize();
    int realParametersCount = args.size();

        Expected(name->token->GetLine(), name->token->GetPosition(),
                 formalParametersCount == realParametersCount,
                 "incorrect arguments in function call");

    for (int i = 0; i < formalParametersCount; ++i)
    {
        SymType* realParamType = args[i]->GetType();
        SymType* formalParamType = type->params->symbols[i]->GetType();

        Expected(args[i]->token->GetLine(), args[i]->token->GetPosition(),
                 realParamType->CanConvertTo(formalParamType),
                 "argument is incompatible with parameter");

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

//-----------------------------------------------------------------------------
NodeArr::NodeArr(int id_, SymType *type_, SyntaxNode* name_, SyntaxNode* index_):
    SyntaxNode(id_, new BaseToken(OPERATOR, SQUARE_LEFT_BRACKET)), type(type_), name(name_), index(index_) {}

NodeArr::~NodeArr() {}

SymType* NodeArr::GetType()
{
    SymType* type = name->GetType();
    Expected(name->token->GetLine(), name->token->GetPosition(),
             (dynamic_cast<SymTypeArray*>(type) || dynamic_cast<SymTypePointer*>(type)),
             "expression must be a pointer to a complete object type");

    SymTypeArray* arrType = dynamic_cast<SymTypeArray*>(type);
    SymTypePointer* pType = dynamic_cast<SymTypePointer*>(type);
    return arrType ? arrType->type : pType->refType;
}

bool NodeArr::IsModifiableLvalue()
{
    SymType* type = GetType();
    return !dynamic_cast<SymTypeArray*>(type) && !dynamic_cast<SymTypeFunc*>(type);
}

bool NodeArr::IsLvalue()
{
    return true;
}

void NodeArr::SetUnUsed(BaseParser& parser)
{
    name->SetUnUsed(parser);
}

//-----------------------------------------------------------------------------
NodeVar::NodeVar(int id_, Symbol* symbol_):
    SyntaxNode(id_, symbol_->name),
    symbol(symbol_)
    {}

NodeVar::~NodeVar() {}

SymType* NodeVar::GetType()
{
    return symbol->GetType();
}

void NodeVar::SetUnUsed(BaseParser& parser)
{
    parser.SetUnUsed(token->GetText());
}

bool NodeVar::IsConstant()
{
//    return *token == CHARACTER
//        || *token == NUMBER_INT
//        || *token- == NUMBER_FLOAT;
    return *token == CONSTANT;
}

bool NodeVar::IsLvalue()
{
    return  *token == IDENTIFIER;
}

bool NodeVar::IsModifiableLvalue()
{
    Symbol* type = symbol->GetType();
    SymTypeScalar* sc = dynamic_cast<SymTypeScalar*>(type);

    if (sc && *symbol->name == IDENTIFIER
        || dynamic_cast<SymTypePointer*>(type))
    {
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
NodePrintf::NodePrintf(int id_, BaseToken* token, SyntaxNode* format_):
    format(format_),
    NodeCall(0, NULL, new SyntaxNode(0, token))
    {}

NodePrintf::~NodePrintf() {}

void NodePrintf::SetUnUsed(BaseParser& parser)
{
    if (args.empty()) return;
    for (int i = 0; i < args.size(); ++i)
    {
        args[i]->SetUnUsed(parser);
    }
}

//-----------------------------------------------------------------------------
NodeDummy::NodeDummy(SymType* type_, SyntaxNode* node):
    NodeUnaryOp(node->id, node->token, node),
    type(type_)
    {}

NodeDummy::~NodeDummy() {}

SymType* NodeDummy::GetType()
{
    return type;
}

void NodeDummy::SetUnUsed(BaseParser& parser)
{
    arg->SetUnUsed(parser);
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

//-----------------------------------------------------------------------------
bool IsIntegralType(SymType* type)
{
    return type == intType || type == charType;
}
