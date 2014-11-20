#include "node.h"
#include "_parser.h"
#include "symbol.h"
#include "statement.h"

static void Indent(int, ostream&);

void Parser::PrintStmtTrees(int indent, ostream& out)//!!!
{
    for (int i = 0, size = stmtStack.size(); i < size; ++i)
    {
        out << "stmt " << i << ":" << endl;
        stmtStack[i]->Print(indent, out);
        out << endl;
    }
}

void Parser::PrintSymTables(ostream& out)
{
    for (int i = 0, size = symStack.tables.size(); i < size; ++i)
    {
        if (symStack.tables[i]->GetSize() > 0)
        {
            out << "table " << i << ":" << endl;
        }
        else
        {
            continue;
        }
        symStack.tables[i]->Print(0, out);
        out << endl;
    }
}

//-----------------------------------------------------------------------------
void SyntaxNode::Print(int indent, ostream& out)
{
    if (!token)
    {
        return;
    }
        Indent(indent, out);
    out << token->GetText();
    if (dynamic_cast<NodeBinaryOp*>(this))
    {
        out << (dynamic_cast<NodeBinaryOp*>(this)->left && dynamic_cast<NodeBinaryOp*>(this)->right ? " <" : "");
    }
    out << endl;
}

void NodeBinaryOp::Print(int indent, ostream& out)
{
    if (left) left->Print(indent+4, out);
    SyntaxNode::Print(indent, out);
    if (right) right->Print(indent+4, out);
}

void NodeUnaryOp::Print(int indent, ostream& out)
{
    arg->Print(indent, out);
}

void NodeCall::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "function: "; name->Print(indent, out);

    if (args.size() > 0)
    {
        Indent(indent, out);
        out << "args: " << endl;
    }
    for (int i = 0, size = args.size(); i < size; ++i)
    {
        args[i]->Print(indent+4, out);
    }
    out << endl;
}

void NodeArr::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "array: " << endl;
    name->Print(indent+4, out);
    Indent(indent, out);
    out << "index: " << endl;
    index->Print(indent+4, out);
}

void NodeVar::Print(int indent, ostream& out)
{
    SyntaxNode::Print(indent, out);
}

void NodePrintf::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "function: "; name->Print(indent, out);
    Indent(indent+4, out);
    out << "format: "; format->Print(indent, out);

    if (args.size() > 0)
    {
        Indent(indent+4, out);
        out << "args: " << endl;
    }
    for (int i = 0, size = args.size(); i < size; ++i)
    {
        args[i]->Print(indent+8, out);
    }
    out << endl;
}

void NodeDummy::Print(int indent, ostream& out)
{
    NodeUnaryOp::Print(indent, out);
}

//-----------------------------------------------------------------------------
void Statement::Print(int indent, ostream& out) {}

void StmtExpr::Print(int indent, ostream& out)
{
    Indent(indent, out);
    !expr
    ? out << "empty expresstion"<< endl
    : expr->Print(indent+4, out); out << endl;
}

void StmtBlock::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "{" << endl;
    if (!locals->symbols.empty())
    {
        locals->Print(indent, out);
    }
    for (int i = 0; i < statements.size(); ++i)
    {
        if (statements[i]) statements[i]->Print(indent, out);
    }
    Indent(indent, out);
    out << "}" << endl;
}

void StmtIf::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "if" << endl;
    condition->Print(indent+4, out);

    Indent(indent, out);
    out << "then" << endl;
    bodyIf->Print(indent+4, out);

    if (bodyElse)
    {
        Indent(indent, out);
        out << "else" << endl;
        bodyElse->Print(indent+4, out);
    }
}

void StmtFor::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "for" << endl;

    Indent(indent, out);
    out << "#1 " << endl;
    if (expr1) expr1->Print(indent, out);

    Indent(indent, out);
    out << "#2 " << endl;
    if (expr2) expr2->Print(indent, out);

    Indent(indent, out);
    out << "#3 " << endl;
    if (expr3) expr3->Print(indent, out);

    if (!body)
    {
        Indent(indent, out);
        out << "empty body" << endl;
    }
    else
    {
        body->Print(indent, out);
    }
}

void StmtWhile::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "while" << endl;
    condition->Print(indent+4, out);
    !body ? out << "empty body" << endl : body->Print(indent, out);
}

void StmtContinue::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "continue" << endl;
}

void StmtBreak::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "break" << endl;
}

void StmtReturn::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "return" << endl;
    if (arg)
    {
        arg->Print(indent+4, out);
    }
}

//-----------------------------------------------------------------------------
void Symbol::Print(int indent, ostream& out)
{
    out << "`" << name->GetText() << "`";
}

void SymTypeArray::Print(int indent, ostream& out)
{
    out << "array " << size << " of ";
    type->Print(indent, out);
}

void SymTypePointer::Print(int indent, ostream& out)
{
    out << "pointer to ";
    refType->Print(indent, out);
}

void SymTypeStruct::Print(int indent, ostream& out)
{
    out << "struct ";
    Symbol::Print(indent, out);
    if (fields->GetSize() > 0)
    {
        Indent(indent+4, out);
        out << endl << "fields:" << endl;
        fields->Print(indent+4, out);
    }
}

void SymTypeFunc::Print(int indent, ostream& out)
{
    //Indent(indent, out);
    out << "function(";

    if (!params->symbols.empty())
    {
        int size = params->symbols.size()-1;
        for (int i = 0; i < size; ++i)
        {
            params->symbols[i]->Print(indent, out); out << ", ";
        }
        params->symbols[size]->Print(indent, out);
    }

    out << ") returning "; type->Print(indent, out); out << endl;

    if (body)
    {
        body->Print(indent, out);
    }
}

void SymVar::Print(int indent, ostream& out)
{
    Indent(indent, out);
    out << "variable "; Symbol::Print(indent, out);
    out << " type of "; type->Print(indent, out);
};

void SymTable::Print(int indent, ostream& out)
{
    for (int i = 0, size = symbols.size(); i < size; ++i)
    {
        symbols[i]->Print(indent, out);
        out << endl;
    }
}

void Indent(int indent, ostream& out)
{
    for (int i = 0; i < indent; ++i)
    {
        out << " ";
    }
}
