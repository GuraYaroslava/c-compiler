#include "exception.h"
#include "_parser.h"

//StmtExpr* Parser::ParseExpr()
//{
//
//}

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
        Expected(lexer.Get()->GetSubType(), SEMICOLON);
        //if (*lexer.Get() != SEMICOLON)
        //{
        //    Error("expacted a `;`");
        //}
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
    Expected(lexer.Get()->GetSubType(), ROUND_LEFT_BRACKET);
    //if (*lexer.Get() != ROUND_LEFT_BRACKET)
    //{
    //    Error("expected a `(`");
    //}
    SyntaxNode* expr1 = ParseExpression();// !!!
    Expected(lexer.Get()->GetSubType(), SEMICOLON);
    //if (*lexer.Get() != SEMICOLON)
    //{
    //    Error("expected a `;`");
    //}
    SyntaxNode* expr2 = ParseExpression();
    Expected(lexer.Get()->GetSubType(), SEMICOLON);
    //if (*lexer.Get() != SEMICOLON)
    //{
    //    Error("expected a `;`");
    //}
    SyntaxNode* expr3 = NULL;

    if (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        expr3 = ParseExpression();
    }
    Expected(lexer.Get()->GetSubType(), ROUND_RIGHT_BRACKET);
    //if (*lexer.Get() != ROUND_RIGHT_BRACKET)
    //{
    //    Error("expected a `)`");
    //}
    Statement* body = ParseStatement();
    inLoop = false;
    return new StmtFor(expr1, expr2, expr3, body);
}

StmtWhile* Parser::ParseWhile()
{
    inLoop = true;
    lexer.Get();
    SyntaxNode* condition = GetCondition();
    Statement* body = ParseStatement();
    inLoop = false;
    return new StmtWhile(condition, body);
}

StmtJump* Parser::ParseJump()
{
    StmtJump* result = NULL;
    BaseToken* token = lexer.Get();
    switch (token->GetSubType())
    {
    case CONTINUE:
        if (!inLoop)
        {
            Error("continue statement not within a loop");
        }
        result = new StmtContinue();
        break;

    case BREAK:
        if (!inLoop)
        {
            Error("break statement not within a loop");
        }
        result = new StmtBreak();
        break;

    case RETURN:
        SyntaxNode* arg = *lexer.Peek() == SEMICOLON ? NULL : ParseExpression();
        result = new StmtReturn(arg);
        break;
    }

    return result;
}

SyntaxNode* Parser::GetCondition()
{
    Expected(lexer.Get()->GetSubType(), ROUND_LEFT_BRACKET);
    //if (*lexer.Get() != ROUND_LEFT_BRACKET)
    //{
    //    Error("expected a `(`");
    //}

    if (*lexer.Peek() == ROUND_RIGHT_BRACKET)
    {
        Error("expected an expression");
    }

    SyntaxNode* condition = ParseExpression();
    Expected(lexer.Get()->GetSubType(), ROUND_RIGHT_BRACKET);
    //if (*lexer.Get() != ROUND_RIGHT_BRACKET)
    //{
    //    Error("expected a `)`");
    //}

    return condition;
}
