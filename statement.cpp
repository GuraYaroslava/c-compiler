#include "statement.h"
#include "symbol.h"

//-----------------------------------------------------------------------------
Statement::Statement() {}

Statement::~Statement() {}

void Statement::SetUnUsed(BaseParser&) {}

//-----------------------------------------------------------------------------
StmtExpr::StmtExpr(SyntaxNode* node): Statement(), expr(node) {}

StmtExpr::~StmtExpr() {}

void StmtExpr::SetUnUsed(BaseParser& parser)
{
    expr->SetUnUsed(parser);
}

//-----------------------------------------------------------------------------
StmtBlock::StmtBlock(): Statement(), statements(NULL), locals(new SymTable()) {}

void StmtBlock::AddStatement(Statement* stmt)
{
    statements.push_back(stmt);
}

void StmtBlock::SetUnUsed(BaseParser& parser)
{
    for (int i = 0, size = statements.size(); i < size; ++i)
    {
        if (statements[i]) statements[i]->SetUnUsed(parser);
    }
}

//-----------------------------------------------------------------------------
StmtIteration::StmtIteration(): start(NULL), inc(NULL), cond(NULL), end(NULL), body(NULL) {}

StmtIteration::~StmtIteration() {}

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

void StmtIf::SetUnUsed(BaseParser& parser)
{
    condition->SetUnUsed(parser);
    bodyIf->SetUnUsed(parser);
    if (bodyElse) bodyElse->SetUnUsed(parser);
}

//-----------------------------------------------------------------------------
StmtFor::StmtFor(SyntaxNode* expr1_,
                 SyntaxNode* expr2_,
                 SyntaxNode* expr3_):
    StmtIteration(),
    expr1(expr1_),
    expr2(expr2_),
    expr3(expr3_)
    {}

void StmtFor::SetUnUsed(BaseParser& parser)
{
    if (expr1) expr1->SetUnUsed(parser);
    if (expr2) expr2->SetUnUsed(parser);
    if (expr3) expr3->SetUnUsed(parser);
    body->SetUnUsed(parser);
}

//-----------------------------------------------------------------------------
StmtWhile::StmtWhile(SyntaxNode* condition_):
    StmtIteration(),
    condition(condition_)
    {}

void StmtWhile::SetUnUsed(BaseParser& parser)
{
    condition->SetUnUsed(parser);
    body->SetUnUsed(parser);
}

//-----------------------------------------------------------------------------
StmtJump::StmtJump(Statement* owner_): Statement(), owner(owner_) {}

//-----------------------------------------------------------------------------
StmtContinue::StmtContinue(Statement* owner): StmtJump(owner) {}

//-----------------------------------------------------------------------------
StmtBreak::StmtBreak(Statement* owner): StmtJump(owner) {}

//-----------------------------------------------------------------------------
StmtReturn::StmtReturn(SyntaxNode* arg_, SymTypeFunc* f):
    StmtJump(NULL),
    arg(arg_),
    func(f)
    {}
