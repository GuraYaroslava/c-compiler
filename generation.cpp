#include "node.h"
#include "_parser.h"
#include "symbol.h"
#include "statement.h"
#include "exception.h"

AsmArgMemory* real4 = new AsmArgMemory("helper4");
AsmArgMemory* real8 = new AsmArgMemory("helper8");

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

void Parser::GenerateCode(bool flag)
{
    //generate consts
    for (int i = 0, size = consts.size(); i < size; ++i)
    {
        consts[i]->GenerateData(generator.data);
    }

    //generate globals symbols
    symStack.Top()->GenerateData(generator.data);
    generator.data.AddCmd(cmdREAL4, real4, new AsmArgFloat(0));
    generator.data.AddCmd(cmdREAL8, real8, new AsmArgFloat(0));

    //generate function declarations
    symStack.Top()->GenerateCode(generator.code);

    //start
    generator.code.AddCmd(new AsmLabel("start"));

    //call main function
    generator.code.AddCmd(cmdSUB, ESP, 4);
    generator.code.AddCmd(cmdCALL, new AsmArgLabel("func_main"));
    generator.code.AddCmd(cmdADD, ESP, 4);

    //end of start
    generator.code.AddCmd(cmdRET, new AsmArg());

    if (flag)
    {
        AsmOptimization();
    }

    //print asm code
    generator.Generate();
}

void SyntaxNode::Generate(AsmCode&) {}

void SyntaxNode::GenerateData(AsmCode&) {}

void SyntaxNode::GenerateLvalue(AsmCode&) {}

void SyntaxNode::FPUGenerate(AsmCode&) {}

void SyntaxNode::PushFromFPUStack(AsmCode& code)
{
    code.AddCmd(cmdFSTP, new AsmArgMemory("helper4"));
    code.AddCmd(cmdPUSH, new AsmArgMemory("helper4"));
}

void NodeBinaryOp::Generate(AsmCode& code)
{
    if (*GetType() == floatType && *token != ASSIGN
        && *token != POINT && *token != ARROW)
    {
        GenerateWithFPU(code);
        return;
    }

    TokenType op = token->GetSubType();

    SymType* leftType = left->GetType();
    SymType* rightType = right->GetType();

    SymTypePointer* leftTypePointer = dynamic_cast<SymTypePointer*>(leftType);
    SymTypePointer* rightTypePointer = dynamic_cast<SymTypePointer*>(rightType);

    if (!leftTypePointer && dynamic_cast<SymTypeArray*>(leftType))
    {
        leftTypePointer = new SymTypePointer(dynamic_cast<SymTypeArray*>(leftType)->type);
    }
    if (!rightTypePointer && dynamic_cast<SymTypeArray*>(rightType))
    {
        rightTypePointer = new SymTypePointer(dynamic_cast<SymTypeArray*>(rightType)->type);
    }

    if (IsAssignment(op))
    {
        right->Generate(code);
        left->GenerateLvalue(code);
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
            int shift = leftTypePointer ? leftTypePointer->refType->GetByteSize() : rightTypePointer->refType->GetByteSize();
            GenerateAddWithPointer(shift, code);
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

void NodeBinaryOp::FPUGenerate(AsmCode& code)
{
    Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, real4, EAX);
    code.AddCmd(cmdFLD, real4);
}

void NodeBinaryOp::GenerateWithFPU(AsmCode& code)
{
    left->FPUGenerate(code);
    right->FPUGenerate(code);

    AsmCmdName cmd;
    if (IsComparison(token->GetSubType()))
    {
        code.AddCmd(cmdXOR, EAX, EAX);
        code.AddCmd(cmdFCOMPP);
        code.AddCmd(cmdFNSTSW, AX);
        code.AddCmd(cmdSAHF);
        code.AddCmd(cmdMOV, EAX, 0);
        switch (token->GetSubType())
        {
        case GREATER:
            cmd = cmdSETB;
            break;
        case GREATER_EQUAL:
            cmd = cmdSETBE;
            break;
        case LESS:
            cmd = cmdSETA;
            break;
        case LESS_EQUAL:
            cmd = cmdSETAE;
            break;
        case EQUAL:
            cmd = cmdSETE;
            break;
        case NOT_EQUAL:
            cmd = cmdSETNE;
            break;
        }
        code.AddCmd(cmd, AL);
        code.AddCmd(cmdPUSH, EAX);
    }
    else
    {
        switch (token->GetSubType())
        {
        case ADDITION:
        case ADD_ASSIGN:
            cmd = cmdFADDP;
            break;
        case SUBSTRACTION:
        case SUB_ASSIGN:
            cmd = cmdFSUBP;
            break;
        case DIVISION:
        case DIV_ASSIGN:
            cmd = cmdFDIVP;
            break;
        case MULTIPLICATION:
        case MUL_ASSIGN:
            cmd = cmdFMULP;
            break;
        default:
            Error(token->GetLine(), token->GetPosition(), "not implemented");
            break;
        }
        code.AddCmd(cmd, ST1, ST0);
        PushFromFPUStack(code);

        if (IsAssignment(token->GetSubType()))
        {
            left->GenerateLvalue(code);
            code.AddCmd(cmdPOP, EAX);
            code.AddCmd(cmdPOP, EBX);
            code.AddCmd(cmdMOV, new AsmArgIndirect(EAX), EBX);
            code.AddCmd(cmdPUSH, EBX);
        }
    }
}

void NodeUnaryOp::Generate(AsmCode& code)
{
    switch(token->GetSubType())
    {
    case SUBSTRACTION:
        arg->Generate(code);
        code.AddCmd(cmdPOP, EAX);
        if (*arg->GetType() == floatType)
        {
            code.AddCmd(cmdPUSH, EAX);
            code.AddCmd(cmdPOP, EAX);
            code.AddCmd(cmdMOV, real4, EAX);
            code.AddCmd(cmdFLD, real4);
            code.AddCmd(cmdFCHS);
            PushFromFPUStack(code);
        }
        else
        {
            code.AddCmd(cmdNEG, EAX);
            code.AddCmd(cmdPUSH, EAX);
        }
        break;

    case ADDITION:
        arg->Generate(code);
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
    switch (token->GetSubType())
    {
    case MULTIPLICATION:
        arg->Generate(code);
        break;
    default:
        throw Exception(token->GetLine(), token->GetPosition(), "O_o");
    }
}

void NodeUnaryOp::FPUGenerate(AsmCode& code)
{
    Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, real4, EAX);
    code.AddCmd(cmdFLD, real4);
}

void NodeCall::Generate(AsmCode& code)
{
    code.AddCmd(cmdSUB, ESP, type->type->GetByteSize());
    for (int i = args.size() - 1; i > -1; --i)
    {
        args[i]->Generate(code);
    }
    code.AddCmd(cmdCALL, new AsmLabel("func_"+name->token->GetText()));
    code.AddCmd(cmdADD, ESP, type->params->GetByteSize());
}

void NodeArr::GenerateLvalue(AsmCode& code)
{
    int shift = dynamic_cast<SymTypeArray*>(type) ?
                dynamic_cast<SymTypeArray*>(type)->type->GetByteSize() :
                dynamic_cast<SymTypePointer*>(type)->refType->GetByteSize();
    name->GenerateLvalue(code);
    index->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, EBX, shift);
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

void NodeVar::GenerateData(AsmCode& code)
{
    SymType* type = symbol->GetType();
    if (type == floatType)
    {
        token->SetText(to_string((long double)(id)));
        code.AddCmd(cmdDD,
                    new AsmArgMemory("var_" + to_string((long double)(id))),
                    new AsmArgFloat(dynamic_cast<TokenVal <float> *>(token)->GetValue()));
    }
    else if (type == stringType)// ???
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
        if (dynamic_cast<SymVar*>(symbol)->local)
        {
            code.AddCmd(cmdMOV, EAX, EBP);
            code.AddCmd(cmdMOV, EBX, symbol->offset);
            code.AddCmd(cmdADD, EAX, EBX);
            code.AddCmd(cmdPUSH, EAX);
        }
        else
        {
            code.AddCmd(cmdPUSH, new AsmArgMemory("var_"+symbol->name->GetText(), true));
        }
    }
    else
    {
        Expected(token->GetLine(), token->GetPosition(), false, "WOW");
    }
}

void NodeVar::Generate(AsmCode& code)
{
    SymType* type = symbol->GetType();

    if (dynamic_cast<SymTypeArray*>(type))
    {
        GenerateLvalue(code);
    }
    else if (*token == IDENTIFIER)
    {
        int size = symbol->GetByteSize();
        int steps = size / 4 + (size % 4 != 0);

        //global
        for (int i = 0; i < steps && !dynamic_cast<SymVar*>(symbol)->local; ++i)
        {
            code.AddCmd(cmdPUSH,
                        new AsmArgMemory("dword ptr [var_"
                                            + token->GetText()
                                            + " + "
                                            + to_string((long double)(4 * (steps - i - 1)))
                                            +"]"));
        }

        //local
        for (int i = 0; i < steps && dynamic_cast<SymVar*>(symbol)->local; ++i)
        {
            code.AddCmd(cmdPUSH, new AsmArgIndirect(EBP, symbol->offset + 4 * (steps - i - 1)));
        }
    }
    else if (type == intType)
    {
        code.AddCmd(cmdMOV, EAX, dynamic_cast<TokenVal <int> *>(token)->GetValue());
        code.AddCmd(cmdPUSH, EAX);
    }
    else if (type == floatType)
    {
        code.AddCmd(cmdPUSH, new AsmArgMemory("var_"+to_string((long double)(id))));//нигде не вызывается
    }
}

void NodeVar::FPUGenerate(AsmCode& code)
{
    if (dynamic_cast<SymVar*>(symbol)->local)
    {
        code.AddCmd(cmdMOV,EAX, new AsmArgIndirect(EBP, symbol->offset));
        code.AddCmd(cmdMOV, real4, EAX);
        code.AddCmd(cmdFLD, real4);
    }
    else
    {
        code.AddCmd(cmdFLD, new AsmArgMemory("var_" + token->GetText()));
    }
}

void NodePrintf::Generate(AsmCode& code)
{
    int size = 0;
    for (int i = args.size() - 1; i > -1; --i)
    {
        SymType* type = args[i]->GetType();
        args[i]->Generate(code);
        size += type->GetByteSize();
        if (*type == floatType && (args[i]->token && !IsComparison(args[i]->token->GetSubType())))
        {
            code.AddCmd(cmdPOP, real4);
            code.AddCmd(cmdFLD, real4);
            code.AddCmd(cmdFSTP, real8);
            code.AddCmd(cmdMOV, EAX, new AsmArgMemory("helper8", true));
            code.AddCmd(cmdPUSH, new AsmArgIndirect(EAX, 4));
            code.AddCmd(cmdPUSH, new AsmArgIndirect(EAX));
            size += 4;
        }
    }
    code.AddCmd(new AsmArgMemory("var_" + to_string((long double)format->id)));
    code.AddCmd(cmdADD, ESP, size);
}

void NodeDummy::Generate(AsmCode& code)
{
    arg->Generate(code);
    SymType* opType = arg->GetType();

    bool resIsFloatArgIsInt = *type == floatType && *opType == intType;
    bool resIsIntArgIsFloat = *type == intType && *opType == floatType;

    if (resIsFloatArgIsInt || resIsIntArgIsFloat)
    {
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdMOV, real4, EAX);
        if (resIsFloatArgIsInt)
        {
            code.AddCmd(cmdFILD, real4);
            code.AddCmd(cmdFSTP, real4);
        }
        else if (resIsIntArgIsFloat)
        {
            code.AddCmd(cmdFLD, real4);
            code.AddCmd(cmdFISTP, real4);
        }
        code.AddCmd(cmdPUSH, real4);
    }
}

void NodeDummy::FPUGenerate(AsmCode& code)
{
    Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV, real4, EAX);
    code.AddCmd(cmdFLD, real4);
}

//-----------------------------------------------------------------------------

void Statement::Generate(AsmCode&)
{

}

void StmtExpr::Generate(AsmCode& code)
{
    if (expr)
    {
        expr->Generate(code);
    }
}

void StmtBlock::Generate(AsmCode& code)
{
    code.AddCmd(cmdSUB, ESP, locals->GetByteSize());
    for (int i = 0, size = statements.size(); i < size; ++i)
    {
        if (statements[i]) statements[i]->Generate(code);
    }
}

void StmtIf::Generate(AsmCode& code)
{
    string key = to_string((long double)rand());
    AsmArgLabel* trueLabel = new AsmArgLabel("if" + key + "_true");
    AsmArgLabel* falseLabel = new AsmArgLabel("if" + key + "_false");
    AsmArgLabel* endLabel = new AsmArgLabel("if" + key + "_end");
    if (condition) condition->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdJNE, trueLabel);
    code.AddCmd(cmdJE, falseLabel);
    code.AddCmd(trueLabel);
    if (bodyIf) bodyIf->Generate(code);
    code.AddCmd(cmdJMP, endLabel);
    code.AddCmd(falseLabel);
    if (bodyElse)
    {
        bodyElse->Generate(code);
    }
    code.AddCmd(endLabel);
}

void StmtIteration::SetStartLabel(string label)
{
    start = new AsmArgLabel(label);
}

void StmtIteration::SetIncLabel(string label)
{
    inc = new AsmArgLabel(label);
}

void StmtIteration::SetCondLabel(string label)
{
    cond = new AsmArgLabel(label);
}

void StmtIteration::SetEndLabel(string label)
{
    end = new AsmArgLabel(label);
}

void StmtFor::Generate(AsmCode& code)
{
    string id = to_string((long double)rand());
    SetStartLabel("for_" + id + "_start");
    SetIncLabel("for_" + id + "_inc");
    SetCondLabel("for_" + id + "_cond");
    SetEndLabel("for_" + id + "_end");
    if (expr1) expr1->Generate(code);
    code.AddCmd(start);
    code.AddCmd(cond);
    if (expr2) expr2->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdJE, end);
    body->Generate(code);
    code.AddCmd(inc);
    if (expr3) expr3->Generate(code);
    code.AddCmd(cmdJMP, cond);
    code.AddCmd(end);
}

void StmtWhile::Generate(AsmCode& code)
{
    string id = to_string((long double)rand());
    SetStartLabel("while_" + id + "_start");
    SetCondLabel("while_" + id + "_cond");
    SetEndLabel("while_" + id + "_end");
    code.AddCmd(start);
    code.AddCmd(cond);
    condition->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdJE, end);
    body->Generate(code);
    code.AddCmd(cmdJMP, cond);
    code.AddCmd(end);
}

void StmtContinue::Generate(AsmCode& code)
{
    if (dynamic_cast<StmtFor*>(owner))
    {
        code.AddCmd(cmdJMP, dynamic_cast<StmtIteration*>(owner)->inc);
    }
    else if (dynamic_cast<StmtWhile*>(owner))
    {
        code.AddCmd(cmdJMP, dynamic_cast<StmtIteration*>(owner)->start);
    }
}

void StmtBreak::Generate(AsmCode& code)
{
    code.AddCmd(cmdJMP, dynamic_cast<StmtIteration*>(owner)->end);
}

void StmtReturn::Generate(AsmCode& code)
{
    arg->Generate(code);
    int size = func->type->GetByteSize();
    int steps = size / 4 + (size % 4 != 0);
    for (int i = 0; i < steps; ++i)
    {
        code.AddCmd(cmdPOP, EAX);
        code.AddCmd(cmdMOV,
                    new AsmArgIndirect(EBP, 4 + func->params->GetByteSize() + size - 4 * (steps - i - 1)),
                    new AsmArgRegister(EAX));
    }
    /*code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV,
                new AsmArgIndirect(EBP, func->params->GetByteSize()),
                new AsmArgRegister(EAX));*/
    code.AddCmd(cmdJMP, func->end);
}

//-----------------------------------------------------------------------------
void Symbol::Generate(AsmCode&)
{

}

void SymTypeFunc::Generate(AsmCode& code)
{
    code.AddCmd(cmdPUSH, EBP);
    code.AddCmd(cmdMOV, EBP, ESP);
    body->Generate(code);
    code.AddCmd(end);
    code.AddCmd(cmdMOV, ESP, EBP);
    code.AddCmd(cmdPOP, EBP);
    code.AddCmd(cmdRET, new AsmArg());
}

void SymVar::Generate(AsmCode& code)
{
    if (dynamic_cast<SymTypeFunc*>(type))
    {
        dynamic_cast<SymTypeFunc*>(type)->end = new AsmArgLabel("end_func_"+name->GetText());
        code.AddCmd(new AsmLabel("func_"+name->GetText()));
        type->Generate(code);
        return;
    }

    int size = type->GetByteSize();
    int dwords = size / 4 + (size % 4 != 0);
    code.AddCmd(cmdDD, new AsmArgMemory("var_"+name->GetText()), new AsmArgDup(dwords));
}

void SymTable::GenerateData(AsmCode& data)
{
    for (int i = 0, size = GetSize(); i < size; ++i)
    {
        SymVar* sym = dynamic_cast<SymVar*>(symbols[i]);
        if (sym && !dynamic_cast<SymTypeFunc*>(sym->type))
        {
            sym->Generate(data);
        }
    }
}

void SymTable::GenerateCode(AsmCode& code)
{
    for (int i = 0, size = GetSize(); i < size; ++i)
    {
        SymVar* sym = dynamic_cast<SymVar*>(symbols[i]);
        if (sym && dynamic_cast<SymTypeFunc*>(sym->type))
        {
            sym->Generate(code);
        }
    }
}
//-----------------------------------------------------------------------------
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
    code.AddCmd(cmdPOP, EAX);
    int size = right->GetType()->GetByteSize();
    int steps = size / 4 + (size % 4 != 0);
    for (int i = 0; i < steps; ++i)
    {
        code.AddCmd(cmdPOP, EBX);
        code.AddCmd(cmdMOV, new AsmArgIndirect(EAX, i * 4), EBX);
    }
    code.AddCmd(cmdMOV, EAX, EBX);
    code.AddCmd(cmdPUSH, EAX);
}

void GenerateMulOrDivOrModAssign(AsmCmdName cmd, AsmCode& code, bool isMod)
{
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdMOV, ECX, EAX);
    code.AddCmd(cmdMOV, EAX, new AsmArgIndirect(ECX));
    code.AddCmd(cmdCDQ);
    code.AddCmd(cmd, EBX);
    code.AddCmd(cmdMOV, new AsmArgIndirect(ECX), isMod ? EDX : EAX);
}

void GenerateAddOrSubAssign(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdMOV, ECX, EAX);
    code.AddCmd(cmdMOV, EAX, new AsmArgIndirect(ECX));
    code.AddCmd(cmdCDQ);
    code.AddCmd(cmd, EAX, EBX);
    code.AddCmd(cmdMOV, new AsmArgIndirect(ECX), EAX);
}

void GenerateBitWiseShiftAssign(AsmCmdName cmd, AsmCode& code)
{
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdPOP, EBX);
    code.AddCmd(cmdMOV, ECX, EBX);
    code.AddCmd(cmd, new AsmArgIndirect(EAX), CL);
    code.AddCmd(cmdPUSH, EAX);
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
    code.AddCmd(cmdIMUL, EAX, EBX);
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
    code.AddCmd(cmdPUSH, isMod ? EDX : EAX);
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
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdPOP, EBX);

    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdMOV, EAX, 0);
    code.AddCmd(cmdSETNE, AL);

    code.AddCmd(cmdCMP, EBX, 0);
    code.AddCmd(cmdMOV, EBX, 0);
    //code.AddCmd(cmdXOR, EBX, EBX);
    code.AddCmd(cmdSETNE, BL);

    code.AddCmd(cmd, EAX, EBX);
    code.AddCmd(cmdCMP, EAX, 0);
    //code.AddCmd(cmdXOR, EBX, EBX);
    code.AddCmd(cmdMOV, EAX, 0);
    code.AddCmd(cmdSETNE, AL);
    code.AddCmd(cmdPUSH, EAX);
}
