#include "node.h"
#include "exception.h"

SymTypeScalar* intType = new SymTypeScalar(new BaseToken("int", 0, 0, KEYWORD, INT));
SymTypeScalar* floatType = new SymTypeScalar(new BaseToken("float", 0, 0, KEYWORD, FLOAT));
SymTypeScalar* charType = new SymTypeScalar(new BaseToken("char", 0, 0, KEYWORD, CHAR));
SymTypePointer* stringType = new SymTypePointer(charType);

SymType* GetWideType(SymType*, SymType*);

bool IsIntegralType(SymType*);
bool IsAssignment(TokenType);
bool IsComparison(TokenType);

static void GenerateAssign(SyntaxNode*, SyntaxNode*, AsmCode&);

static void GenerateOperator(AsmCmdName, AsmCode&, bool isMod = false);
static void GenerateMulOrDivOrModAssign(AsmCmdName, AsmCode&, bool isMod = false);

static void GenerateBitWiseShift(AsmCmdName cmd, AsmCode&);
static void GenerateBitWiseShiftAssign(AsmCmdName cmd, AsmCode&);

static void GenerateAddOrSubInts(AsmCmdName, AsmCode&);
static void GenerateAddWithPointer(int, AsmCode&);
static void GenerateSubWithPointer(SyntaxNode*, SyntaxNode*, AsmCode&);
static void GenerateAddOrSubAssign(AsmCmdName, AsmCode&);

static void GenerateCmp(AsmCmdName, AsmCode&);
static void GenerateLogicAndOr(AsmCmdName, AsmCode&);

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

        /*if (leftTypePointer || rightTypePointer)
        {
            Expected(token->GetLine(), token->GetPosition(),
                     leftTypePointer && (IsIntegralType(rightType) || rightType->CanConvertTo(leftType))
                     || rightTypePointer && (IsIntegralType(leftType) || leftType->CanConvertTo(rightType)),
                     "operand types are incompatible");
            return intType;
        }*/

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

    if (IsAssignment(op))
    {
        left->GenerateLvalue(code);
        right->Generate(code);
    }
    else if (op != POINT && op != ARROW)
    {
        left->Generate(code);
        right->Generate(code);
    }

    switch(op)
    {
    case ASSIGN:
        GenerateAssign(left, right, code);
        break;

    case MUL_ASSIGN:
        GenerateMulOrDivOrModAssign(cmdIMUL, code);
        break;

    case DIV_ASSIGN:
        GenerateMulOrDivOrModAssign(cmdIDIV, code);
        break;

    case MOD_ASSIGN:
        GenerateMulOrDivOrModAssign(cmdIDIV, code, true);
        break;

    case BIT_SHIFT_LEFT:
        GenerateBitWiseShift(cmdSHL, code);
        break;

    case BIT_SHIFT_RIGHT:
        GenerateBitWiseShift(cmdSHR, code);
        break;

    case BIT_SHIFT_LEFT_ASSIGN:
        GenerateBitWiseShiftAssign(cmdSHL, code);
        break;

    case BIT_SHIFT_RIGHT_ASSIGN:
        GenerateBitWiseShiftAssign(cmdSHR, code);
        break;

    case ADDITION:
        if (!leftTypePointer && !rightTypePointer)
        {
            GenerateAddOrSubInts(cmdADD, code);
        }
        if (leftTypePointer || rightTypePointer)
        {
            if (!leftTypePointer)
            {
                swap(left, right);
                swap(leftTypePointer, rightTypePointer);
            }
            GenerateAddWithPointer(leftTypePointer->refType->GetByteSize(), code);
        }
        break;

    case SUBSTRACTION:
        if (!leftTypePointer && !rightTypePointer)
        {
            GenerateAddOrSubInts(cmdSUB, code);
        }
        if (leftTypePointer || rightTypePointer)
        {
            GenerateSubWithPointer(left, right, code);
        }
        break;

    case MULTIPLICATION:
        GenerateOperator(cmdIMUL, code);
        break;

    case DIVISION:
        GenerateOperator(cmdIDIV, code);
        break;

    case MODULO:
        GenerateOperator(cmdIDIV, code, true);
        break;

    case EQUAL:
        GenerateCmp(cmdSETE, code);
        break;

    case NOT_EQUAL:
        GenerateCmp(cmdSETNE, code);
        break;

    case LESS:
        GenerateCmp(cmdSETL, code);
        break;

    case LESS_EQUAL:
        GenerateCmp(cmdSETLE, code);
        break;

    case GREATER:
        GenerateCmp(cmdSETG, code);
        break;

    case GREATER_EQUAL:
        GenerateCmp(cmdSETGE, code);
        break;

    case AND:
        GenerateLogicAndOr(cmdIMUL, code);
        break;

    case OR:
        GenerateLogicAndOr(cmdADD, code);
        break;

    case ADD_ASSIGN:
        GenerateAddOrSubAssign(cmdADD, code);
        break;

    case SUB_ASSIGN:
        GenerateAddOrSubAssign(cmdSUB, code);
        break;

    case BIT_AND_ASSIGN:
    case BIT_AND:
        //GenerateOperator(cmdAND, code);
        GenerateAddOrSubInts(cmdAND, code);
        break;

    case BIT_OR_ASSIGN:
    case BIT_OR:
        //GenerateOperator(cmdOR, code);
        GenerateAddOrSubInts(cmdOR, code);
        break;

    case BIT_XOR_ASSIGN:
    case BIT_XOR:
        //GenerateOperator(cmdXOR, code);
        GenerateAddOrSubInts(cmdXOR, code);
        break;

    case POINT:
        GenerateLvalue(code);
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdPUSH, new AsmArgIndirect(EAX));
        break;

    case ARROW:
        GenerateLvalue(code);
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdPUSH, new AsmArgIndirect(EAX));
        break;
    }
}

void NodeBinaryOp::GenerateLvalue(AsmCode& code)
{
    if (IsAssignment(token->GetSubType()))
    {
        Generate(code);
        code.AddCmd(cmdPOP, EAX);
        left->GenerateLvalue(code);
        return;
    }

    if (*token == POINT)
    {
        left->GenerateLvalue(code);
    }
    else if (*token == ARROW)
    {
        left->Generate(code);
    }

    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, EBX, dynamic_cast<NodeVar*>(right)->symbol->offset);
    code.AddCmd(cmdADD, EAX, EBX);
    code.AddCmd(cmdPUSH, EAX);
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

void NodeUnaryOp::Generate(AsmCode& code)
{
    //code.AddCmd(cmdPUSH, EAX);
    switch(token->GetSubType())
    {
    case SUBSTRACTION:
        arg->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        if (*arg->GetType() == floatType)
        {

        } else
        {
            code.AddCmd(cmdNEG, EAX);
            code.AddCmd(cmdPUSH, EAX);
        }
        break;

    case ADDITION:
        arg->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdPUSH, EAX);
        break;

    case NOT:
        arg->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdCMP, EAX, 0);
        code.AddCmd(cmdSETE, AL);
        code.AddCmd(cmdPUSH, EAX);
        break;

    case BIT_AND:
        arg->GenerateLvalue(code);
        break;

    case BIT_NOT:
        arg->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdNOT, EAX);
        code.AddCmd(cmdPUSH, EAX);
        break;

    case MULTIPLICATION:
        arg->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        int size = dynamic_cast<SymTypePointer*>(arg->GetType())->refType->GetByteSize();
        int steps = size / 4 + (size % 4 != 0);
        code.AddCmd(cmdMOV, EBX, EAX);
        for (int i = 0; i < steps; ++i)
        {
            code.AddCmd(cmdMOV, new AsmArgRegister(EAX), new AsmArgIndirect(EBX, (steps - i - 1) * 4));
            code.AddCmd(cmdPUSH, EAX);
        }
        break;
    }
}

void NodeUnaryOp::GenerateLvalue(AsmCode& code)
{
    //*pointer
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
NodeCall::NodeCall(int id_, SymTypeFunc* type_, SyntaxNode* name_):
    SyntaxNode(id_, name_->token),
    type(type_),
    name(name_),
    args(NULL)
    {}

NodeCall::~NodeCall() {}

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
    code.AddCmd(cmdSUB, ESP, type->type->GetByteSize());
    for (int i = args.size() - 1; i > -1; --i)
    {
        args[i]->Generate(code);
    }
    code.AddCmd(cmdCALL, new AsmLabel(name->token->GetText()));
    code.AddCmd(cmdADD, ESP, type->params->GetByteSize());
}

//-----------------------------------------------------------------------------
NodeArr::NodeArr(int id_, SymTypeArray*type_, SyntaxNode* name_, SyntaxNode* index_):
    SyntaxNode(id_, NULL), type(type_), name(name_), index(index_) {}

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

void NodeArr::Print(int width, int indent, ostream& out)
{
    out << setw(indent) << "array: " << endl;
    name->Print(width, indent+width, out);
    out << setw(indent) << "index: " << endl;
    index->Print(width, indent+width, out);
}

void NodeArr::GenerateLvalue(AsmCode& code)
{
    name->GenerateLvalue(code);
    index->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, EBX, type->type->GetByteSize());
    code.AddCmd(cmdIMUL, EAX, EBX);
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdADD, EAX, EBX);
    code.AddCmd(cmdPUSH, EAX);
}

void NodeArr::Generate(AsmCode& code)
{
    GenerateLvalue(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdPUSH, new AsmArgIndirect(EAX));
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

bool NodeVar::IsLvalue()
{
    Symbol* type = symbol->GetType();
    if (!dynamic_cast<SymTypeScalar*>(type))
    {
        throw Exception(token->GetLine(),
                        token->GetPosition(),
                        "NODE VAR HAVE NOT SCALAR TYPE");
    }

    return  type->name->GetSubType() == IDENTIFIER;
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

void NodeVar::Print(int width, int indent, ostream& out)
{
    SyntaxNode::Print(width, indent, out);
}

void NodeVar::GenerateData(AsmCode& code)
{
    SymType* type = symbol->GetType();
    if (type == intType)
    {

    }
    else if (type == floatType)
    {
        code.AddCmd(cmdDD,
                    new AsmArgMemory("var_" + to_string((long double)(id))),
                    new AsmArgFloat(dynamic_cast<TokenVal <float> *>(token)->GetValue()));
    }
    else if (type == charType)
    {
        code.AddCmd(cmdDD,
                    new AsmArgMemory("var_" + to_string((long double)(id))),
                    GenAsmString(token->GetText()));
    }
    else if (type == stringType)
    {
        code.AddCmd(cmdDB,
                    new AsmArgMemory("var_" + to_string((long double)(id))),
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

        for (int i = 0; i < steps && !dynamic_cast<SymVar*>(symbol)->local; ++i)
        {
            code.AddCmd(cmdPUSH,
                        new AsmArgMemory("dword ptr ["
                                            + token->GetText()
                                            //+ " + "
                                            //+ to_string((long double)(4 * (steps - i - 1)))
                                            +"]"));
        }

        for (int i = 0; i < steps && dynamic_cast<SymVar*>(symbol)->local; ++i)
        {
            code.AddCmd(cmdPUSH, new AsmArgIndirect(EBP, symbol->offset + 4 * (steps - i - 1)));//!!!
        }
        return;
    }

    SymType* type = symbol->GetType();
    if (type == intType)
    {
        code.AddCmd(cmdMOV, EAX, dynamic_cast<TokenVal <int> *>(token)->GetValue());
        code.AddCmd(cmdPUSH, EAX);
    }
}

//-----------------------------------------------------------------------------
NodePrintf::NodePrintf(int id_, BaseToken* token, SyntaxNode* format_):
    format(format_),
    NodeCall(0, NULL, new SyntaxNode(0, token))
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
    }
    code.AddCmd(new AsmArgMemory("var_" + to_string((long double)format->id)));
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
    NodeUnaryOp(node->id, NULL, node),
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

//-----------------------------------------------------------------------------
bool IsIntegralType(SymType* type)
{
    return type == intType || type == charType;
}

bool IsAssignment(TokenType cmd)
{
    return cmd == ASSIGN
        || cmd == ADD_ASSIGN || cmd == BIT_AND_ASSIGN
        || cmd == SUB_ASSIGN || cmd == BIT_XOR_ASSIGN
        || cmd == MUL_ASSIGN || cmd == BIT_OR_ASSIGN
        || cmd == DIV_ASSIGN || cmd == BIT_SHIFT_LEFT_ASSIGN
        || cmd == MOD_ASSIGN || cmd == BIT_SHIFT_RIGHT_ASSIGN;
}

bool IsComparison(TokenType cmd)
{
    return cmd == EQUAL      || cmd == NOT_EQUAL
        || cmd == LESS       || cmd == GREATER
        || cmd == LESS_EQUAL || cmd == GREATER_EQUAL;
}

void GenerateAssign(SyntaxNode* left, SyntaxNode* right, AsmCode& code)
{
    code.AddCmd(cmdPOP, EBX);
    int size = right->GetType()->GetByteSize();
    int steps = size / 4 + (size % 4 != 0);
    for (int i = 0; i < steps; ++i)
    {
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdMOV, new AsmArgIndirect(EAX, i * 4), new AsmArgRegister(EBX));
    }
    code.AddCmd(cmdMOV, EAX, EBX);
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateMulOrDivOrModAssign(AsmCmdName cmd, AsmCode& code, bool isMod)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, ECX, EAX);
    code.AddCmd(cmdMOV, new AsmArgRegister(EAX), new AsmArgIndirect(ECX));
    code.AddCmd(cmdCDQ);
    code.AddCmd(cmd, EBX);
    AsmArgRegister* reg = isMod ? new AsmArgRegister(EDX) : new AsmArgRegister(EAX);
    code.AddCmd(cmdMOV, new AsmArgIndirect(ECX), reg);
}

void GenerateAddOrSubAssign(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, ECX, EAX);
    code.AddCmd(cmdMOV, new AsmArgRegister(EAX), new AsmArgIndirect(ECX));
    code.AddCmd(cmdCDQ);
    code.AddCmd(cmd, EAX, EBX);
    code.AddCmd(cmdMOV, new AsmArgIndirect(ECX), new AsmArgRegister(EAX));
}

void GenerateBitWiseShiftAssign(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, EDX, EAX);
    code.AddCmd(cmdMOV, new AsmArgRegister(EAX), new AsmArgIndirect(EDX));
    code.AddCmd(cmdMOV, ECX, EBX);
    code.AddCmd(cmd, EAX, CL);
    code.AddCmd(cmdMOV, new AsmArgIndirect(EDX), new AsmArgRegister(EAX));
}

void GenerateBitWiseShift(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, ECX, EBX);
    code.AddCmd(cmd, EAX, CL);
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateAddOrSubInts(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmd, EAX, EBX);
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateAddWithPointer(int shift, AsmCode& code)
{
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, EBX, shift);
    code.AddCmd(cmdIMUL, EBX, EAX);
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdADD, EAX, EBX);
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateSubWithPointer(SyntaxNode* left, SyntaxNode* right, AsmCode& code)
{
    SymTypePointer* leftTypePointer = dynamic_cast<SymTypePointer*>((left)->GetType());
    SymTypePointer* rightTypePointer = dynamic_cast<SymTypePointer*>((right)->GetType());

    code.AddCmd(cmdPOP, EAX);
    if (leftTypePointer && rightTypePointer)
    {
        code.AddCmd(cmdPOP, EBX);
        code.AddCmd(cmdSUB, EAX, EBX);
        code.AddCmd(cmdMOV, EBX, leftTypePointer->refType->GetByteSize());
        code.AddCmd(cmdCDQ);
        code.AddCmd(cmdIDIV, EBX);
    }
    else
    {
        code.AddCmd(cmdMOV, EBX, leftTypePointer->refType->GetByteSize());
        code.AddCmd(cmdIMUL, EBX, EAX);
        code.AddCmd(cmdPOP, EBX);
        code.AddCmd(cmdSUB, EAX, EBX);
    }
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateOperator(AsmCmdName cmd, AsmCode& code, bool isMod)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCDQ);
    code.AddCmd(cmd, EBX);
    if (isMod)
    {
        code.AddCmd(cmdMOV, EAX, EDX);
    }
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateCmp(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCMP, EAX, EBX);
    code.AddCmd(cmdMOV, EAX, 0);
    code.AddCmd(cmd, AL);
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateLogicAndOr(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdCMP, EAX, 0);// set flags: sub
    code.AddCmd(cmdMOV, EAX, 0);
    code.AddCmd(cmdSETNE, AL);// set 01h / 00h

    code.AddCmd(cmdCMP, EBX, 0);
    code.AddCmd(cmdMOV, EBX, 0);
    code.AddCmd(cmdSETNE, BL);

    code.AddCmd(cmd, EAX, EBX);
    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdMOV, EAX, 0);
    code.AddCmd(cmdSETNE, AL);
    code.AddCmd(cmdPUSH, EAX);
}
