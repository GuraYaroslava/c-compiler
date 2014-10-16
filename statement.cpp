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
    if (expr)
    {
        expr->Generate(code);
    }
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
    code.AddCmd(cmdSUB, ESP, locals->GetByteSize());//!!!
    for (int i = 0, size = statements.size(); i < size; ++i)
    {
        statements[i]->Generate(code);
    }
}

//-----------------------------------------------------------------------------
StmtIteration::StmtIteration(): start(NULL), inc(NULL), cond(NULL), end(NULL), body(NULL) {}

StmtIteration::~StmtIteration()
{

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

void StmtIteration::SetBody(Statement* body_)
{
    body = body_;
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
    string key = to_string((long double)rand());
    AsmArgLabel* trueLabel = new AsmArgLabel("if" + key + "_true");
    AsmArgLabel* falseLabel = new AsmArgLabel("if" + key + "_false");
    AsmArgLabel* endLabel = new AsmArgLabel("if" + key + "_end");
    condition->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdJNE, trueLabel);
    code.AddCmd(cmdJE, falseLabel);
    code.AddCmd(trueLabel);
    bodyIf->Generate(code);
    code.AddCmd(cmdJMP, endLabel);
    code.AddCmd(falseLabel);
    if (bodyElse)
    {
        bodyElse->Generate(code);
    }
    code.AddCmd(endLabel);
}

//-----------------------------------------------------------------------------
StmtFor::StmtFor(SyntaxNode* expr1_,
                 SyntaxNode* expr2_,
                 SyntaxNode* expr3_):
    StmtIteration(),
    expr1(new StmtExpr(expr1_)),
    expr2(new StmtExpr(expr2_)),
    expr3(new StmtExpr(expr3_))
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
    string id = to_string((long double)rand());
    SetStartLabel("for_" + id + "_start");
    SetIncLabel("for_" + id + "_inc");
    SetCondLabel("for_" + id + "_cond");
    SetEndLabel("for_" + id + "_end");
    expr1->Generate(code);
    code.AddCmd(start);
    code.AddCmd(cond);
    expr2->Generate(code);
    code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdCMP, EAX, 0);
    code.AddCmd(cmdJE, end);
    body->Generate(code);
    code.AddCmd(inc);
    expr3->Generate(code);
    code.AddCmd(cmdJMP, cond);
    code.AddCmd(end);
}

//-----------------------------------------------------------------------------
StmtWhile::StmtWhile(SyntaxNode* condition_):
    StmtIteration(),
    condition(condition_)
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

//-----------------------------------------------------------------------------
StmtJump::StmtJump(Statement* owner_): Statement(), owner(owner_) {}

//-----------------------------------------------------------------------------
StmtContinue::StmtContinue(Statement* owner): StmtJump(owner) {}

void StmtContinue::StmtPrint(ostream& out, int indent)
{
    out << "continue" << endl;
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

//-----------------------------------------------------------------------------
StmtBreak::StmtBreak(Statement* owner): StmtJump(owner) {}

void StmtBreak::StmtPrint(ostream& out, int indent)
{
    out << "break" << endl;
}

void StmtBreak::Generate(AsmCode& code)
{
    code.AddCmd(cmdJMP, dynamic_cast<StmtIteration*>(owner)->end);
}

//-----------------------------------------------------------------------------
StmtReturn::StmtReturn(SyntaxNode* arg_, SymTypeFunc* f):
    StmtJump(NULL),
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
    /*code.AddCmd(cmdPOP, EAX);
    code.AddCmd(cmdMOV,
                new AsmArgIndirect(EBP, func->params->GetByteSize()),
                new AsmArgRegister(EAX));*/
    code.AddCmd(cmdJMP, func->end);
}
