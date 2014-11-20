#include "exception.h"
#include "_parser.h"

Statement* Parser::ParseStatement()
{
    switch (lexer.Peek()->GetSubType())
    {
    case IF:
        return ParseIf();
    case FOR:
        return ParseFor();
    case WHILE:
        return ParseWhile();
    case FIGURE_LEFT_BRACKET:
        return ParseBlock(true);
    case CONTINUE:
    case BREAK:
    case RETURN:
        return ParseJump();
    default:
        StmtExpr* stmt = new StmtExpr(ParseExpression());
        Expected(*lexer.Get() == SEMICOLON, "expected a `;`");
        return stmt;
    }
}

StmtBlock* Parser::ParseBlock(bool inFunction)
{
    lexer.Get();
    StmtBlock* result = new StmtBlock();
    result->locals->shift = inFunction ? symStack.Top()->shift + symStack.Top()->GetByteSize() : 4;
    symStack.Push(result->locals);

    while (*lexer.Peek() != FIGURE_RIGHT_BRACKET)
    {
        if (*lexer.Peek() == STRUCT
            || dynamic_cast<SymType*>(symStack.Find(lexer.Peek()->GetText())))
        {
            ParseDeclaration();
            for (int i = 0, size = stmtStack.size(); i < size; ++i)
            {
                result->AddStatement(stmtStack[i]);
            }
            stmtStack.clear();
        }
        else
        {
            result->AddStatement(ParseStatement());
        }
    }

    if (inFunction)
    {
        lexer.Get();
    }

    symStack.Pop();

    return result;
}

StmtIf* Parser::ParseIf()
{
    lexer.Get();
    SyntaxNode* condition = GetCondition();

    Statement* trueBranch = ParseStatement();
    Statement* falseBranch = NULL;
    if (*lexer.Peek() == ELSE)
    {
        lexer.Get();
        falseBranch = ParseStatement();
    }
    return new StmtIf(condition, trueBranch, falseBranch);
}

StmtFor* Parser::ParseFor()
{
    lexer.Get();
    Expected(*lexer.Get() == ROUND_LEFT_BRACKET, "expected a `(`");
    SyntaxNode* expr1 = ParseExpression();

    Expected(*lexer.Get() == SEMICOLON, "expected a `;`");
    SyntaxNode* expr2 = ParseExpression();

    Expected(*lexer.Get() == SEMICOLON, "expected a `;`");
    SyntaxNode* expr3 = NULL;

    if (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        expr3 = ParseExpression();
    }
    Expected(*lexer.Get() == ROUND_RIGHT_BRACKET, "expected a `)`");

    StmtFor* result = new StmtFor(expr1, expr2, expr3);
    StmtIteration* tmp = parseIter;
    parseIter = result;

    Statement* body = ParseStatement();
    result->SetBody(body);

    parseIter = tmp;
    return result;
}

StmtWhile* Parser::ParseWhile()
{
    lexer.Get();
    SyntaxNode* condition = GetCondition();

    StmtWhile* result = new StmtWhile(condition);
    StmtIteration* tmp = parseIter;
    parseIter = result;

    Statement* body = ParseStatement();
    result->SetBody(body);

    parseIter = tmp;
    return result;
}

StmtJump* Parser::ParseJump()
{
    StmtJump* result = NULL;
    BaseToken* token = lexer.Get();
    switch (token->GetSubType())
    {
    case CONTINUE:
        Expected(parseIter, "continue statement not within a loop");
        result = new StmtContinue(parseIter);
        break;

    case BREAK:
        Expected(parseIter, "break statement not within a loop");
        result = new StmtBreak(parseIter);
        break;

    case RETURN:
        Expected(parseFunc.back() != NULL, "return statement not within a func");//как быть в случае ф-ции, объ€вленной внутри др. ф-ции???
        SyntaxNode* arg = *lexer.Peek() == SEMICOLON ? NULL : ParseExpression();
        result = new StmtReturn(arg, parseFunc.back());
        break;
    }

    Expected(*lexer.Get() == SEMICOLON, "expected `;`");
    return result;
}

SyntaxNode* Parser::GetCondition()
{
    Expected(*lexer.Get() == ROUND_LEFT_BRACKET, "expected a `(`");
    if (*lexer.Peek() == ROUND_RIGHT_BRACKET)
    {
        Error("expected an expression");
    }

    SyntaxNode* condition = ParseExpression();
    Expected(*lexer.Get() == ROUND_RIGHT_BRACKET, "expected a `)`");

    return condition;
}
