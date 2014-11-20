#include "exception.h"
#include "_parser.h"

#define POSTFIX 14
#define UNARY 13
#define MAX 15

void Parser::Parse()
{
    BaseToken* token = lexer.Peek();

    (*token == STRUCT || dynamic_cast<SymType*>(symStack.Find(token->GetText()))) ?
        ParseDeclaration() : stmtStack.push_back(ParseStatement());

    if (*lexer.Peek() == SEMICOLON)
    {
        lexer.Get();
    }
}

SyntaxNode* Parser::ParseExpression(int precedence)
{
    if (precedence == UNARY)
    {
        BaseToken* oper = GetUnary();
        if (oper)
        {
            SyntaxNode* expr = ParseExpression(precedence);
            SyntaxNode* node = new NodeUnaryOp(counter++, oper, expr);

            // type check
            node->GetType();
            return node;
        }
    }

    if (precedence == MAX)
    {
        return ParsePrimaryExpression();
    }

    SyntaxNode* left = ParseExpression(precedence+1);
    if (!left)
    {
        return NULL;
    }

    BaseToken* oper = lexer.Peek();
    TokenType type = oper->GetType();
    TokenType subType = oper->GetSubType();
    while (type == OPERATOR && precedences[subType] == precedence)
    {
        lexer.Get();
        if (precedence == POSTFIX)
        {
            if (subType == SQUARE_LEFT_BRACKET)
            {
                ParseArrIndex(left);
            }

            if (subType == ROUND_LEFT_BRACKET)
            {
                ParseFuncCall(left);
            }

            if (subType == POINT || subType == ARROW)
            {
                ParseMemberSelection(left, oper);
            }
        }
        else
        {
            SyntaxNode* right = ParseExpression(precedence + (right_assoc_oper[subType] == true ? 0 : 1));
            left = new NodeBinaryOp(counter++, left, oper, right);
        }

        // type check
        left->GetType();

        oper = lexer.Peek();
        type = oper->GetType();
        subType = oper->GetSubType();
    }

    return left;
};

SyntaxNode* Parser::ParsePrimaryExpression()
{
    if (*lexer.Peek() == SEMICOLON)
    {
        return NULL;
    }

    SyntaxNode* result = NULL;
    BaseToken* token = lexer.Get();

    if (*token == IDENTIFIER)
    {
        Symbol* symbol = symStack.Find(token->GetText());
        if (!symbol && !parseFunc.empty())
        {
            symbol = parseFunc.back()->params->Find(token->GetText());
        }
        Expected(symbol != NULL, "identifier is undefined");
        result = new NodeVar(counter++, symbol);
        symStack.SetUsed(token->GetText());
    }
    else if (*token == CONSTANT || *token == STRING)
    {
        switch (token->GetSubType())
        {
        case NUMBER_INT:
            result = new NodeVar(counter++, new SymVar(token, intType));
            break;
        case NUMBER_FLOAT:
            result = new NodeVar(counter++, new SymVar(token, floatType));
            break;
        case CHARACTER:
            result = new NodeVar(counter++, new SymVar(token, charType));
            break;
        case STRING:
            result = new NodeVar(counter++, new SymVar(token, stringType));
            break;
        }
        consts.push_back(result);
    }
    else if (*token == OPERATOR && *token == ROUND_LEFT_BRACKET)
    {
        result = ParseExpression();
        Expected(lexer.Get()->GetSubType(), ROUND_RIGHT_BRACKET);
    }
    else if (*token == PRINTF)
    {
        result = ParsePrintf(token);
    }
    else if (*token == KEYWORD)
    {
        return NULL;
    }
    else
    {
        Error("expected an expression: "+token->GetText());
    }
    return result;
}

void Parser::ParseFuncCall(SyntaxNode*& node)
{
    SymTypeFunc* type = dynamic_cast<SymTypeFunc*>(node->GetType());
    Expected(type != NULL, "expression must have (pointer-to-) function type");
    //symStack.SetUsed(node->token->GetText());
    node = new NodeCall(counter++, type, node);
    while (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        SyntaxNode* arg = ParseExpression(precedences[COMMA]+1);
        Expected(*lexer.Peek() != EOF_, "expected a `)`");

        if (*lexer.Peek() == COMMA)
        {
            lexer.Get();
        }

        dynamic_cast<NodeCall*>(node)->AddArg(arg);
    }

    lexer.Get();
}

void Parser::ParseArrIndex(SyntaxNode*& node)
{
    SymType* type = dynamic_cast<SymTypeArray*>(node->GetType());
    if (!type)
    {
        type = dynamic_cast<SymTypePointer*>(node->GetType());
    }
    Expected(type != NULL, "expression must have array type");
    Expected(*lexer.Peek() != SQUARE_RIGHT_BRACKET, "unknown size");
    SyntaxNode* index = ParseExpression();
    node = new NodeArr(counter++, type, node, index);

    Expected(lexer.Get()->GetSubType(), SQUARE_RIGHT_BRACKET);
}

void Parser::ParseMemberSelection(SyntaxNode*& node, BaseToken* oper)
{
    Expected(lexer.Peek()->GetSubType(), IDENTIFIER);

    SymTypeStruct* st = NULL;
    SymType* type = node->GetType();
    if (dynamic_cast<SymTypePointer*>(type))
    {
        st = dynamic_cast<SymTypeStruct*>(dynamic_cast<SymTypePointer*>(type)->refType);
        Expected(st != NULL, "expression must have pointer-to-struct type");
    }
    else
    {
        st = dynamic_cast<SymTypeStruct*>(type);
        Expected(st != NULL, "expression must have struct type");
    }

    Symbol* symbol = st->fields->Find(lexer.Get()->GetText());
    Expected(symbol != NULL, "struct has no this member");
    node = new NodeBinaryOp(counter++, node, oper, new NodeVar(counter++, symbol));
}

SyntaxNode* Parser::ParsePrintf(BaseToken* token)
{
    NodePrintf* result = NULL;
    Expected(*lexer.Get() == ROUND_LEFT_BRACKET, "expected a `(`");

    SyntaxNode* format = ParseExpression(precedences[COMMA] + 1);
    SymType* type = format->GetType();
    Expected(type == stringType, "expected parameter of char*");

    result = new NodePrintf(counter++, token, format);
    if (*lexer.Peek() == COMMA)
    {
        lexer.Get();
        while (true)
        {
            SyntaxNode* arg = ParseExpression(precedences[COMMA] + 1);
            Expected(arg != NULL, "expected argument");
            result->AddArg(arg);
            if (*lexer.Peek() == ROUND_RIGHT_BRACKET)
            {
                break;
            }
            Expected(*lexer.Get() == COMMA, "expected a `,`");
        }
    }
    Expected(*lexer.Get() == ROUND_RIGHT_BRACKET, "expected a `)`");
    return result;
}

BaseToken* Parser::GetUnary()
{
    BaseToken* oper = lexer.Peek();
    if (oper && *oper == OPERATOR && unary_oper[oper->GetSubType()])
    {
        return lexer.Get();
    }
    return NULL;
}
