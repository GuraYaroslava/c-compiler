#include "statement.h"
#include "symbol.h"

//-----------------------------------------------------------------------------
Statement::Statement() {}

Statement::~Statement() {}

void Statement::StmtPrint(ostream& out, int indent) {};

void Statement::Generate(AsmCode&)
{

}

//-----------------------------------------------------------------------------
StmtExpr::StmtExpr(SyntaxNode* node): Statement(), expr(node) {}

void StmtExpr::StmtPrint(ostream &out, int indent)
{
    out << "exprassion:" << endl;
    if (!expr)
    {
        out << "empty expresstion"<< endl;
        return;
    }
    expr->Print(indent, indent, out);
    out << endl;
}

void StmtExpr::Generate(AsmCode& code)
{
    expr->Generate(code);
}

//-----------------------------------------------------------------------------
StmtBlock::StmtBlock(): Statement(), statements(NULL), locals(new SymTable()) {}

void StmtBlock::AddStatement(Statement* stmt)
{
    statements.push_back(stmt);
}

void StmtBlock::StmtPrint(ostream& out, int indent)
{
    out << "{" << endl;
    if (!locals->symbols.empty())
    {
        locals->Print(out);
    }
    if (!statements.empty())
    {
        for (int i = 0; i < statements.size(); ++i)
        {
            statements[i]->StmtPrint(out, indent*2);
        }
    }
    out << "}" << endl;
}

void StmtBlock::Generate(AsmCode& code)
{
    for (int i = 0, size = statements.size(); i < size; ++i)
    {
        statements[i]->Generate(code);
    }
}

//-----------------------------------------------------------------------------
StmtIf::StmtIf(SyntaxNode* conditioin_, Statement* bodyIf_, Statement* bodyElse_):
    Statement(),
    condition(conditioin_),
    bodyIf(bodyIf_),
    bodyElse(bodyElse_)
    {}

void StmtIf::StmtPrint(ostream& out, int indent)
{
    out << "if" << endl;
    condition->Print(indent, indent, out);

    out << "then" << endl;
    bodyIf->StmtPrint(out, indent);

    if (bodyElse)
    {
        out << "else" << endl;
        bodyElse->StmtPrint(out, indent);
    }
}

void StmtIf::Generate(AsmCode& code)
{
}

//-----------------------------------------------------------------------------
StmtFor::StmtFor(SyntaxNode* expr1_,
                 SyntaxNode* expr2_,
                 SyntaxNode* expr3_,
                 Statement* body_):
    Statement(),
    expr1(new StmtExpr(expr1_)),
    expr2(new StmtExpr(expr2_)),
    expr3(new StmtExpr(expr3_)),
    body(body_)
    {}

StmtFor::StmtFor(StmtExpr* expr1_,
                 StmtExpr* expr2_,
                 StmtExpr* expr3_,
                 Statement* body_):
    Statement(),
    expr1(expr1_),
    expr2(expr2_),
    expr3(expr3_),
    body(body_)
    {}

void StmtFor::StmtPrint(ostream& out, int indent)
{
    out << "for" << endl;

    out << "#1 ";
    expr1->StmtPrint(out, indent);

    out << "#2 ";
    expr2->StmtPrint(out, indent);

    out << "#3 ";
    expr3->StmtPrint(out, indent);

    out << "body: ";
    if (!body)
    {
        out << "empty" << endl;
    }
    else
    {
        out << endl;
        body->StmtPrint(out, indent);
    }
}

void StmtFor::Generate(AsmCode& code)
{
}

//-----------------------------------------------------------------------------
StmtWhile::StmtWhile(SyntaxNode* condition_, Statement* body_):
    Statement(),
    condition(condition_),
    body(body_)
    {}

void StmtWhile::StmtPrint(ostream& out, int indent)
{
    out << "while" << endl;
    condition->Print(indent, indent, out);

    out << "body:";
    if (!body)
    {
        out << "empty" << endl;
    }
    else
    {
        out << endl;
        body->StmtPrint(out, indent);
    }
}

void StmtWhile::Generate(AsmCode& code)
{
}

//-----------------------------------------------------------------------------
StmtJump::StmtJump(): Statement() {}

//-----------------------------------------------------------------------------
StmtContinue::StmtContinue(): StmtJump() {}

void StmtContinue::StmtPrint(ostream& out, int indent)
{
    out << "continue" << endl;
}

void StmtContinue::Generate(AsmCode& code)
{
}

//-----------------------------------------------------------------------------
StmtBreak::StmtBreak(): StmtJump() {}

void StmtBreak::StmtPrint(ostream& out, int indent)
{
    out << "break" << endl;
}

void StmtBreak::Generate(AsmCode& code)
{
}

//-----------------------------------------------------------------------------
StmtReturn::StmtReturn(SyntaxNode* arg_, SymTypeFunc* f):
    StmtJump(),
    arg(arg_),
    func(f)
    {}

void StmtReturn::StmtPrint(ostream& out, int indent)
{
    out << "return" << endl;
    if (arg)
    {
        arg->Print(indent, indent, out);
    }
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
    code.AddCmd(cmdJMP, func->end);
}
