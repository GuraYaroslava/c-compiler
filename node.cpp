#include "node.h"
#include "exception.h"

static int counter = 0;

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

void SyntaxNode::Generate(AsmCode&)
{

}

void SyntaxNode::GenerateData(AsmCode&)
{

}

void SyntaxNode::GenerateLvalue(AsmCode&)
{

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

void NodeBinaryOp::Generate(AsmCode& code)
{
    TokenType op = token->GetSubType();

    SymType* leftType = left->GetType();
    SymType* rightType = right->GetType();

    SymTypePointer* leftTypePointer = dynamic_cast<SymTypePointer*>(leftType);
    SymTypePointer* rightTypePointer = dynamic_cast<SymTypePointer*>(rightType);

    if (op == ASSIGN)
    {
        right->Generate(code);
        left->GenerateLvalue(code);
        code.AddCmd(cmdPOP, EAX);
        int size = right->GetType()->GetByteSize();
        int steps = size / 4 + (size % 4 != 0);
        for (int i = 0; i < steps; i++)
        {
            code.AddCmd(cmdPOP, EBX);
            code.AddCmd(cmdMOV, new AsmArgIndirect(EAX, i * 4), new AsmArgRegister(EBX));
        }
        code.AddCmd(cmdMOV, EAX, EBX);
        code.AddCmd(cmdPUSH, EAX);
    }
    else if (op == ADDITION || op == SUBSTRACTION)
    {
        if (!leftTypePointer && !rightTypePointer)
        {
            if (!leftTypePointer)
            {
                swap(left, right);
                swap(leftTypePointer, rightTypePointer);
            }
            left->Generate(code);
            right->Generate(code);
            code.AddCmd(cmdPOP, EAX);
            code.AddCmd(cmdPOP, EBX);
            code.AddCmd(op == ADDITION ? cmdADD : cmdSUB, EAX, EBX);
            code.AddCmd(cmdPUSH, EAX);
        }
        else if (leftTypePointer || rightTypePointer)
        {
            if (op == ADDITION)
            {
                if (!leftTypePointer)
                {
                    swap(left, right);
                    swap(leftTypePointer, rightTypePointer);
                }
                left->Generate(code);
                right->Generate(code);
                code.AddCmd(cmdPOP, EAX);
                code.AddCmd(cmdMOV, EBX, leftTypePointer->refType->GetByteSize());
                code.AddCmd(cmdIMUL, EBX, EAX);
                code.AddCmd(cmdPOP, EBX);
                code.AddCmd(cmdADD, EAX, EBX);
                code.AddCmd(cmdPUSH, EAX);
            }
            else if (op == SUBSTRACTION)
            {
                left->Generate(code);
                right->Generate(code);
                if (leftTypePointer && rightTypePointer)
                {
                    //расстояние = модуль разности //!!!
                    code.AddCmd(cmdPOP, EAX);
                    code.AddCmd(cmdPOP, EBX);
                    code.AddCmd(cmdSUB, EAX, EBX);
                    code.AddCmd(cmdMOV, EBX, leftTypePointer->refType->GetByteSize());
                    code.AddCmd(cmdCDQ);
                    code.AddCmd(cmdIDIV, EBX);
                    code.AddCmd(cmdPUSH, EAX);
                    return;
                }
                code.AddCmd(cmdPOP, EAX);
                code.AddCmd(cmdMOV, EBX, leftTypePointer->refType->GetByteSize());
                code.AddCmd(cmdIMUL, EBX, EAX);
                code.AddCmd(cmdPOP, EBX);
                code.AddCmd(cmdSUB, EAX, EBX);
                code.AddCmd(cmdPUSH, EAX);
            }
        }
    }
	else if (op == MULTIPLICATION)
	{
        left->Generate(code);
        right->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdPOP, EBX);
		code.AddCmd(cmdIMUL, EAX, EBX);
		code.AddCmd(cmdPUSH, EAX);
	}
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

void NodeUnaryOp::Generate(AsmCode& code)
{
    //code.AddCmd(cmdPUSH, EAX);
    arg->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    if (*token == SUBSTRACTION)
        if (*arg->GetType() == floatType)
        {

        } else
        {
            code.AddCmd(cmdNEG, EAX);
            code.AddCmd(cmdPUSH, EAX);
        }
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
    out << setw(indent) << "function: " << endl;
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

void NodeCall::Generate(AsmCode& code)
{
    code.AddCmd(cmdSUB, ESP, type->GetByteSize());//!!!
    for (int i = args.size() - 1; i > -1; --i)
    {
        args[i]->Generate(code);
    }
    code.AddCmd(cmdCALL, new AsmLabel(name->token->GetText()));
    code.AddCmd(cmdADD, ESP, type->params->GetByteSize());//!!!
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

void NodeVar::GenerateData(AsmCode& code)
{
    SymType* type = symbol->GetType();
    if (type == intType)
    {
        //code.AddCmd(cmdDD,
        //            new AsmArgMemory("int_" + to_string((long double)counter++)),
        //            new AsmArgInt(dynamic_cast<TokenVal <int> *>(token)->GetValue()));
    }
    else if (type == floatType)
    {
        code.AddCmd(cmdDD,
                    new AsmArgMemory("float_" + to_string((long double)counter++)),
                    new AsmArgFloat(dynamic_cast<TokenVal <float> *>(token)->GetValue()));
    }
    else if (type == charType)
    {
        code.AddCmd(cmdDD,
                    new AsmArgMemory("ch_" + to_string((long double)counter++)),
                    GenAsmString(token->GetText()));
    }
    else if (type == stringType)
    {
        code.AddCmd(cmdDB,
                    new AsmArgMemory("str_" + to_string((long double)counter++)),
                    GenAsmString(token->GetText()));
    }
}

void NodeVar::GenerateLvalue(AsmCode& code)
{
    if (*token == IDENTIFIER)
    {
        code.AddCmd(cmdPUSH, new AsmArgMemory(symbol->name->GetText(), true));//!!!

        //code.AddCmd(cmdMOV, EAX, EBP);
        //code.AddCmd(cmdMOV, EBX, OFFSET);
        //code.AddCmd(cmdADD, EAX, EBX);
        //code.AddCmd(cmdPUSH, EAX);
        return;
    }

    SymType* type = symbol->GetType();
    if (type == intType)
    {
        throw Exception(token->GetLine(),
                token->GetPosition(),
                "WOW");
    }
    else if (type == floatType)
    {
        throw Exception(token->GetLine(),
                token->GetPosition(),
                "WOW");
    }
    else if (type == charType)
    {
        throw Exception(token->GetLine(),
                token->GetPosition(),
                "WOW");
    }
    else if (type == stringType)
    {
        throw Exception(token->GetLine(),
                token->GetPosition(),
                "WOW");
    }
}

void NodeVar::Generate(AsmCode& code)
{
    if (*token == IDENTIFIER)
    {
        int size = symbol->GetByteSize();
        int steps = size / 4 + (size % 4 != 0);
        //global
        for (int i = 0; i < steps; ++i)
        {
            code.AddCmd(cmdPUSH,
                        new AsmArgMemory("dword ptr ["
                                            + token->GetText()
                                            + " + "
                                            + to_string((long double)(4 * (steps - i - 1))) +"]"));
        }
        return;
    }

    SymType* type = symbol->GetType();
    if (type == intType)
    {
        code.AddCmd(cmdMOV, EAX, dynamic_cast<TokenVal <int> *>(token)->GetValue());
        code.AddCmd(cmdPUSH, EAX);
    }
    else if (type == floatType)
    {
        
    }
    else if (type == charType)
    {
        
    }
    else if (type == stringType)
    {
        
    }
}

//-----------------------------------------------------------------------------
NodePrintf::NodePrintf(BaseToken* token, SyntaxNode* format_):
    format(format_),
    NodeCall(NULL, new SyntaxNode(token))
    {}

NodePrintf::~NodePrintf() {}

void NodePrintf::Generate(AsmCode& code)
{
    int size = 0;
    for (int i = args.size() - 1; i > -1; --i)
    {
        SymType* type = args[i]->GetType();
        args[i]->Generate(code);
        size += type->GetByteSize();
        //if (*type == floatType)
        //{
        //    code.AddCmd(cmdPOP, real4);
        //    code.AddCmd(cmdFLD, real4);
        //    code.AddCmd(cmdFSTP, real8);
        //    code.AddCmd(cmdMOV, makeArg(EAX), makeArgMemory(real8name, true));
        //    code.AddCmd(cmdPUSH, makeIndirectArg(EAX, 4));
        //    code.AddCmd(cmdPUSH, makeIndirectArg(EAX));
        //    size += 4;
        //}
    }
    code.AddCmd(new AsmArgMemory("str_" + to_string((long double)counter++)));
    code.AddCmd(cmdADD, ESP, size);
}

void NodePrintf::Print(int width, int indent, ostream& out)
{
    out << setw(indent) << "function: " << endl;
    name->Print(width, indent+width, out);

    out << setw(indent) << "format: " << endl;
    format->Print(width, indent+width, out);

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

void NodeDummy::Generate(AsmCode& code)
{
    arg->Generate(code);
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
