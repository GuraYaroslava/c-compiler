#include "exception.h"
#include "_parser.h"

Statement* Parser::ParseStatement()
{
    BaseToken* token = lexer.Peek();
    if (*token == IF)
    {
        return ParseIf();
    }
    else if (*token == FOR)
    {
        return ParseFor();
    }
    else if (*token == WHILE)
    {
        return ParseWhile();
    }
    else if (*token == FIGURE_LEFT_BRACKET)
    {
        return ParseBlock();
    }
    else if (*token == CONTINUE || *token == BREAK || *token == RETURN)
    {
        return ParseJump();
    }
    else
    {
        StmtExpr* stmt = new StmtExpr(ParseExpression());
        Expected(*lexer.Get() == SEMICOLON, "expacted a `;`");
        return stmt;
    }
}

StmtBlock* Parser::ParseBlock()
{
    lexer.Get();
    StmtBlock* result = new StmtBlock();
    symStack.Push(result->locals);

    while (*lexer.Peek() != FIGURE_RIGHT_BRACKET)
    {
        if (*lexer.Peek() == STRUCT
            || dynamic_cast<SymType*>(symStack.Find(lexer.Peek()->GetText())))
        {
            ParseDeclaration();
        }
        else
        {
            result->AddStatement(ParseStatement());
        }
    }

    for (int i = 0, size = nodeStack.size(); i < size; ++i)
    {
        result->AddStatement(new StmtExpr(nodeStack[i]));
    }

    nodeStack.clear();
    lexer.Get();
    symStack.Pop();

    return result;
}

StmtIf* Parser::ParseIf()
{
    lexer.Get();
    SyntaxNode* condition = GetCondition();

    Statement* trueBranch = ParseStatement();
    Statement* falseBranch = NULL;
    if (*lexer.Get() == ELSE)
    {
        falseBranch = ParseStatement();
    }
    return new StmtIf(condition, trueBranch, falseBranch);
}

StmtFor* Parser::ParseFor()
{
    inLoop = true;
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
    inLoop = false;
    return result;
}

StmtWhile* Parser::ParseWhile()
{
    inLoop = true;
    lexer.Get();
    SyntaxNode* condition = GetCondition();

    StmtWhile* result = new StmtWhile(condition);
    StmtIteration* tmp = parseIter;
    parseIter = result;

    Statement* body = ParseStatement();
    result->SetBody(body);

    parseIter = tmp;
    inLoop = false;//!!!
    return result;
}

StmtJump* Parser::ParseJump()
{
    StmtJump* result = NULL;
    BaseToken* token = lexer.Get();
    switch (token->GetSubType())
    {
    case CONTINUE:
        Expected(inLoop, "continue statement not within a loop");
        result = new StmtContinue();
        break;

    case BREAK:
        Expected(inLoop, "break statement not within a loop");
        result = new StmtBreak();
        break;

    case RETURN:
        Expected(parseFunc != NULL, "return statement not within a func");// is it possible?
        SyntaxNode* arg = *lexer.Peek() == SEMICOLON ? NULL : ParseExpression();
        result = new StmtReturn(arg, parseFunc);
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
