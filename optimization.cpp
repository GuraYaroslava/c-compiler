#include "node.h"
#include "_parser.h"
#include "symbol.h"
#include "statement.h"

void Parser::Optimize()
{
    symStack.SetUsed("main");
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (int i = 0; i < symStack.tables.size(); ++i)
        {
            symStack.tables[i]->Optimize(flag, *this);
        }
    }
}

SyntaxNode* SyntaxNode::Optimize(bool&, BaseParser& parser)
{
    return this;
}

SyntaxNode* SyntaxNode::FoldConsts(bool&, BaseParser& parser)
{
    return this;
}

float SyntaxNode::Calculate()
{
    return 0;
}

float NodeBinaryOp::Calculate()
{
    float fl = left->Calculate();
    float fr = right->Calculate();
    int il = (int)fl;
    int ir = (int)fr;

    switch (token->GetSubType())
    {
    case COMMA:
        return float(fr);
    case OR:
        return float(fl || fr);
    case AND:
        return float(fl && fr);
    case BIT_OR:
        return float(il |  ir);
    case BIT_XOR:
        return float(il ^  ir);
    case BIT_AND:
        return float(il &  ir);
    case EQUAL:
        return float(fl == fr);
    case NOT_EQUAL:
        return float(fl != fr);
    case LESS:
        return float(fl <  fr);
    case GREATER:
        return float(fl >  fr);
    case LESS_EQUAL:
        return float(fl <= fr);
    case GREATER_EQUAL:
        return float(fl >= fr);
    case BIT_SHIFT_LEFT:
        return float(il << ir);
    case BIT_SHIFT_RIGHT:
        return float(il >> ir);
    case ADDITION:
        return float(fl +  fr);
    case SUBSTRACTION:
        return float(fl -  fr);
    case MULTIPLICATION:
        return float(fl *  fr);
    case DIVISION:
        return float(fl /  fr);
    case MODULO:
        return float(il %  ir);
    //ERROR
    }
}

SyntaxNode* NodeBinaryOp::Optimize(bool& successOprimization, BaseParser& parser)
{
    return FoldConsts(successOprimization, parser);
}

SyntaxNode* NodeBinaryOp::FoldConsts(bool& successOprimization, BaseParser& parser)
{
    left = left->Optimize(successOprimization, parser);
    right = right->Optimize(successOprimization, parser);

    if (left->IsConstant() && right->IsConstant())
    {
        if (GetType() == intType) // CHAR??? FLOAT???
        {
            SymVar* symbol = new SymVar(new TokenVal <int> ("", 0, 0, CONSTANT, NUMBER_INT, 0), intType);
            dynamic_cast<TokenVal <int> *>(symbol->name)->SetValue((int)Calculate());
            symbol->name->SetText(to_string((long double)dynamic_cast<TokenVal <int> *>(symbol->name)->GetValue()));
            successOprimization = true;
            return new NodeVar(left->id, symbol);
        }
    }
    return this;
}

float NodeUnaryOp::Calculate()
{
    float fl = arg->Calculate();
    switch (token->GetSubType())
    {
    case SUBSTRACTION:
        return -fl;
    case NOT:
        return !fl;
    default:
        return fl;
    }
}

SyntaxNode* NodeUnaryOp::Optimize(bool& successOprimization, BaseParser& parser)
{
    return FoldConsts(successOprimization, parser);
}

SyntaxNode* NodeUnaryOp::FoldConsts(bool& successOprimization, BaseParser& parser)
{
    arg = arg->Optimize(successOprimization, parser);

    if (arg->IsConstant())
    {
        SymType* type = GetType();
        if (type == intType || type == charType)
        {
            SymVar* symbol = new SymVar(new TokenVal <int> ("", 0, 0, CONSTANT, NUMBER_INT, 0), intType);
            dynamic_cast<TokenVal <int> *>(symbol->name)->SetValue((int)Calculate());
            symbol->name->SetText(to_string((long double)dynamic_cast<TokenVal <int> *>(symbol->name)->GetValue()));
            successOprimization = true;
            return new NodeVar(arg->id, symbol);
        }
        return this;
    }
    return this;
}

SyntaxNode* NodeCall::Optimize(bool& successOprimization, BaseParser& parser)
{
    for (int i = 0, size = args.size(); i < size; ++i)
    {
        args[i] = args[i]->Optimize(successOprimization, parser);
    }
    return this;
}

SyntaxNode* NodeArr::Optimize(bool& successOprimization, BaseParser& parser)
{
    index = index->Optimize(successOprimization, parser);
    return this;
}

float NodeVar::Calculate()
{
    SymType* type = GetType();
    switch (token->GetSubType())
    {
    case NUMBER_INT:
        return (float)dynamic_cast<TokenVal <int> *>(token)->GetValue();
    case NUMBER_FLOAT:
        return dynamic_cast<TokenVal <float> *>(token)->GetValue();
    case CHARACTER:
        return (float)dynamic_cast<TokenVal <int> *>(token)->GetValue();
    }
}

SyntaxNode* NodeDummy::Optimize(bool& successOprimization, BaseParser& parser)
{
    arg = arg->Optimize(successOprimization, parser);
    return arg;
}

float NodeDummy::Calculate()
{
    return arg->Calculate();
}

//-----------------------------------------------------------------------------
Statement* Statement::Optimize(bool& successOprimization, BaseParser&)
{
    successOprimization = false || successOprimization;
    return this;
}

Statement* StmtExpr::Optimize(bool& successOprimization, BaseParser& parser)
{
    expr = expr ? expr->Optimize(successOprimization, parser) : NULL;
    return this;
}

Statement* StmtBlock::Optimize(bool& successOprimization, BaseParser& parser)
{
    if (statements.empty())
    {
        return NULL;
    }

    parser.PushLocals(locals);
    for (int i = 0; i < statements.size(); ++i)
    {
        if (statements[i])
        {
            statements[i] = statements[i]->Optimize(successOprimization, parser);
        }
        if (!statements[i])
        {
            delete statements[i]; statements[i] = NULL;
            statements.erase(statements.begin() + i);
            continue;
        }
        if (dynamic_cast<StmtReturn*>(statements[i]) && i+1 < statements.size())
        {
            for (int j = i+1; j < statements.size(); ++j)
            {
                statements[j]->SetUnUsed(parser);
                Delete(j);
            }
            successOprimization = true;
        }
    }
    parser.PopLocals();
    locals->Optimize(successOprimization, parser);
    return this;
}

Statement* StmtIf::Optimize(bool& successOprimization, BaseParser& parser)
{
    return DeadCodeEliminate(successOprimization, parser);
}

Statement* StmtIf::DeadCodeEliminate(bool& successOprimization, BaseParser& parser)
{
    condition = condition->Optimize(successOprimization, parser);
    if (!condition->IsConstant())
    {
        bodyIf = bodyIf->Optimize(successOprimization, parser);
        bodyElse = bodyElse ? bodyElse->Optimize(successOprimization, parser) : NULL;
        return this;
    }

    successOprimization = true;

    if (!condition->Calculate())
    {
        if (bodyElse)
        {
            bodyIf->SetUnUsed(parser);
            delete bodyIf; bodyIf = NULL;
            return bodyElse;
        }
        //delete condition; condition = NULL;
        //delete bodyIf; bodyIf = NULL;
        this->SetUnUsed(parser);
        return NULL;
    }
    else
    {
        if (bodyElse)
        {
            successOprimization = true;
            bodyElse->SetUnUsed(parser);
            delete bodyElse; bodyElse = NULL;
            return bodyIf;
        }
        return bodyIf;
    }
}

Statement* StmtFor::Optimize(bool& successOprimization, BaseParser& parser)
{
    if (expr2)
    {
        expr2 = expr2->Optimize(successOprimization, parser);
        if (expr2->IsConstant() && !expr2->Calculate())
        {
            //delete expr1; expr1 = NULL;
            //delete expr2; expr2 = NULL;
            //delete expr3; expr3 = NULL;
            //delete body; body = NULL;
            successOprimization = true;
            this->SetUnUsed(parser);
            return NULL;
        }
    }
    if (expr1) expr1 = expr1->Optimize(successOprimization, parser);
    if (expr3) expr3 = expr3->Optimize(successOprimization, parser);
    body = body->Optimize(successOprimization, parser);
    return this;
}

Statement* StmtWhile::Optimize(bool& successOprimization, BaseParser& parser)
{
    condition = condition->Optimize(successOprimization, parser);
    if (condition->IsConstant() && !condition->Calculate())
    {
        //delete condition; condition = NULL;
        //delete body; body = NULL;
        successOprimization = true;
        this->SetUnUsed(parser);
        return NULL;
    }
    body = body->Optimize(successOprimization, parser);
    return this;
}

Statement* StmtReturn::Optimize(bool& successOprimization, BaseParser& parser)
{
    arg = arg->Optimize(successOprimization, parser);
    return this;
}

//-----------------------------------------------------------------------------
void Symbol::Optimize(bool& successOprimization, BaseParser&)
{
    successOprimization = false || successOprimization;
}

void SymTypeFunc::Optimize(bool& successOprimization, BaseParser& parser)
{
    body->Optimize(successOprimization, parser);
}

void SymVar::Optimize(bool& successOprimization, BaseParser& parser)
{
    if (dynamic_cast<SymTypeFunc*>(type))
    {
        type->Optimize(successOprimization, parser);
    }
}

void SymTable::Optimize(bool& successOprimization, BaseParser& parser)
{
    for (int i = 0; i < GetSize(); ++i)
    {
        if (dynamic_cast<SymVar*>(symbols[i]) && dynamic_cast<SymVar*>(symbols[i])->used <= 0)
        {
            successOprimization = true;
            symbols[i]->SetUnUsed(parser);
            Delete(i);
            continue;
        }
        symbols[i]->Optimize(successOprimization, parser);
    }
}

void SymTable::Delete(int i)
{
    delete symbols[i]; symbols[i] = NULL;
    symbols.erase(symbols.begin() + i);
}

void StmtBlock::Delete(int j)
{
    delete statements[j]; statements[j] = NULL;
    statements.erase(statements.begin() + j);
}
