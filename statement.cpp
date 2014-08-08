#include "statement.h"
#include "symbol.h"

Statement::Statement() {}

Statement::~Statement() {}

void Statement::StmtPrint(ostream &out/*, int indent*/) {};

//-----------------------------------------------------------------------------
StmtBlock::StmtBlock(): Statement(), statements(NULL), locals(new SymTable()) {}

void StmtBlock::StmtPrint(ostream &out/*, int indent*/)
{
    out << "Block_begin" << endl;
    if (!locals->symbols.empty())
    {
        out << "Locals_begin" << endl;
        locals->Print(out);
        out << "Locals_end" << endl;
    }
    if (!statements.empty())
    {
        for (int i=0; i<statements.size(); i++)
            statements[i]->StmtPrint(out);
    }
    out << "Block_end" << endl;
}

StmtAssignment::StmtAssignment(SyntaxNode *_left, SyntaxNode *_right):
    Statement(),
    left(_left),
    right(_right) {}

void StmtAssignment::StmtPrint(ostream &out/*, int indent*/) 
{
    out << "Assignment:" << endl;
    left->Print(10, 5, out);
    out << "=" << endl;
    right->Print(10, 5, out);
    out << endl;
}

//-----------------------------------------------------------------------------
StmtExpr::StmtExpr(SyntaxNode *root): Statement(), expr(root) {}

void StmtExpr::StmtPrint(ostream &out/*, int indent*/) 
{
    out << "Exprassion:" << endl;
    if (!expr) {out << "empty expresstion"<< endl; return;}
    expr->Print(10, 0, out);
    out << endl;
}

//-----------------------------------------------------------------------------
StmtIf::StmtIf(SyntaxNode *_conditioin,  Statement *_if_body,  Statement *_else_body):
    Statement(),
    condition(_conditioin),
    if_body(_if_body),
    else_body(_else_body) {}

void StmtIf::StmtPrint(ostream &out)
{
    out << "If_begin" << endl;
    out << "Condition:" << endl;
    condition->Print(10, 5, out);
    out << "Body (if):" << endl;
    if_body->StmtPrint(out);
    if (else_body) 
    {
        out << "Body (else):" << endl;
        else_body->StmtPrint(out);
    }
    out << "If_end" << endl;
}

//-----------------------------------------------------------------------------
StmtFor::StmtFor(SyntaxNode *_expr1, SyntaxNode *_expr2, SyntaxNode *_expr3, Statement *_body):
    Statement(),
    expr1(new StmtExpr(_expr1)),
    expr2(new StmtExpr(_expr2)),
    expr3(new StmtExpr(_expr3)),
    body(_body)  {}

StmtFor::StmtFor(StmtExpr *_expr1, StmtExpr *_expr2, StmtExpr *_expr3, Statement *_body):
    Statement(),
    expr1(_expr1),
    expr2(_expr2),
    expr3(_expr3),
    body(_body) {}

void StmtFor::StmtPrint(ostream &out/*, int indent*/)
{
    out << "For_begin" << endl;
    out << "#1 ";
    expr1->StmtPrint(out);
    out << "#2 ";
    expr2->StmtPrint(out);
    out << "#3 ";
    expr3->StmtPrint(out);
    out << "Body:" << endl;
    if (!body) out << "Empty." << endl;
    else body->StmtPrint(out);
    out << "For_end" << endl;
}

//-----------------------------------------------------------------------------
StmtWhile::StmtWhile(SyntaxNode *_condition, Statement *_body):
    Statement(),
    condition(_condition),
    body(_body) {}

void StmtWhile::StmtPrint(ostream &out/*, int indent*/) 
{
    out << "While_begin" << endl;
    out << "Condition:" << endl;
    condition->Print(10, 5, out);
    out << "Body:" << endl;
    if (!body) out << "Empty." << endl;
    else body->StmtPrint(out);
    out << "While_end" << endl;
}

//-----------------------------------------------------------------------------
StmtJump::StmtJump(): Statement() {}

//-----------------------------------------------------------------------------
StmtContinue::StmtContinue(): StmtJump() {}

void StmtContinue::StmtPrint(ostream &out/*, int indent*/)
{
    out << "contionue" << endl;
}

//-----------------------------------------------------------------------------
StmtBreak::StmtBreak(): StmtJump() {}

void StmtBreak::StmtPrint(ostream &out/*, int indent*/)
{
    out << "break" << endl;
}

//-----------------------------------------------------------------------------
StmtReturn::StmtReturn(SyntaxNode *_arg): StmtJump(), arg(_arg) {}

void StmtReturn::StmtPrint(ostream &out/*, int indent*/) 
{
    out << "return" << endl;
    if (arg) arg->Print(10, 5, out);
}