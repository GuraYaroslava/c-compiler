#include "exception.h"
#include "_parser.h"

void Parser::ParseDeclaration()
{
    SymType* type = ParseTypeSpecifier();
    Symbol* symbol = NULL;

    if (*lexer.Peek() == SEMICOLON)
    {
        lexer.Get();
        return;
    }
    else
    {
        symbol = ParseDeclarator(type);
    }

    while (true)
    {
        symStack.Add(symbol);

        if (*lexer.Peek() == ASSIGN)
        {
            BaseToken* oper = lexer.Get();
            SyntaxNode* left = new NodeVar(counter++, symbol);
            SyntaxNode* right = ParseExpression(precedences[COMMA]+1);
            nodeStack.push_back(node);
            NodeBinaryOp* node = new NodeBinaryOp(counter++, left, oper, right);
            node->GetType();
        }

        if (*lexer.Peek() == SEMICOLON)
        {
            lexer.Get();
            break;
        }

        if (parseFunc)
        {
            parseFunc = NULL;
            break;
        }

        Expected(lexer.Peek()->GetSubType(), COMMA);

        lexer.Get();
        symbol = ParseDeclarator(type);
    }
}

SymType* Parser::ParseTypeSpecifier()
{
    SymType* result = NULL;
    BaseToken* token = lexer.Get();

    if (*token == STRUCT)
    {
        result = ParseStructSpecifier();
    }
    else
    {
        result = dynamic_cast<SymType*>(symStack.Find(token->GetText()));
    }

    return result;
}

SymTypeStruct* Parser::ParseStructSpecifier()
{
    SymTypeStruct* result = NULL;
    if (*lexer.Peek() != IDENTIFIER)
    {
        string n = to_string((long double)counter++);
        BaseToken* dummy = new BaseToken("abstract-struct-"+n, 0, 0, IDENTIFIER, IDENTIFIER);
        result = new SymTypeStruct(dummy);
    }
    else
    {
        BaseToken* name = lexer.Get();
        result = new SymTypeStruct(name);
    }

    //---------------------------------------------------------------------------
    symStack.Push(result->fields);
    //expected either a definition or a tag name
    Expected(lexer.Get()->GetSubType(), FIGURE_LEFT_BRACKET);
    ParseStructDeclaration();
    symStack.Pop();
    //---------------------------------------------------------------------------

    symStack.Add(result);
    return result;
}

void Parser::ParseStructDeclaration()
{
    if (*lexer.Peek() == FIGURE_RIGHT_BRACKET)
    {
        lexer.Get();
        return;
    }

    SymType* type = ParseTypeSpecifier();
    Symbol* declarator = ParseDeclarator(type);

    while (true)
    {
        symStack.Add(declarator, 2);

        Expected(*lexer.Peek() != ASSIGN, "data member initializer is not allowed");

        if (*lexer.Peek() == COMMA)
        {
            lexer.Get();
            declarator = ParseDeclarator(type);
        }
        else if (*lexer.Peek() == SEMICOLON)
        {
            lexer.Get();
            if (*lexer.Peek() == FIGURE_RIGHT_BRACKET)
            {
                lexer.Get();
                break;
            }
            type = ParseTypeSpecifier();
            declarator = ParseDeclarator(type);
        }
        else
        {
            Error("expected `,` or `;`");
        }
    }
}

SymVar* Parser::ParseDeclarator(SymType* type, bool parseParams)
{
    SymVar* result = NULL;

    //pointer
    while (*lexer.Peek() == MULTIPLICATION)
    {
        type = new SymTypePointer(type);
        lexer.Get();
    }

    //direct-declarator
    if (*lexer.Peek() == ROUND_LEFT_BRACKET)
    {
        lexer.Get();
        result =  ParseDeclarator(type);
        Expected(lexer.Peek()->GetSubType(), ROUND_RIGHT_BRACKET);
        lexer.Get();
        return result;
    }

    BaseToken* t = lexer.Peek();
    if (!parseParams && *lexer.Peek() != IDENTIFIER)
    {
        Error("exepcted an identifier");
    }
    else if (parseParams && *lexer.Peek() != IDENTIFIER)
    {
        string n = to_string((long double)counter++);
        BaseToken* dummy = new BaseToken("abstract-"+n, 0, 0, IDENTIFIER, IDENTIFIER);
        result = new SymVar(dummy, type);
    }
    else if (symStack.Find(lexer.Peek()->GetText()))
    {
        Error("redefinition");
    }
    else
    {
        result = new SymVar(lexer.Get(), type);
    }

    BaseToken* token = lexer.Peek();
    if (*token == SQUARE_LEFT_BRACKET)
    {
        lexer.Get();
        Expected(*lexer.Peek() != SQUARE_RIGHT_BRACKET, "unknown size");

        SyntaxNode* index = ParseExpression();
        SymType* indexType = index->GetType();
        Expected(indexType == intType && indexType->CanConvertTo(intType),
                 "expression must be an integral constant expression");
        Expected(*index->token != IDENTIFIER, "expression must have a constant value");

        Expected(lexer.Get()->GetSubType(), SQUARE_RIGHT_BRACKET);

        int size = dynamic_cast<TokenVal <int> *>(index->token)->GetValue();
        result->SetType(new SymTypeArray(size, type));
    }
    else if (*token == ROUND_LEFT_BRACKET)
    {
        lexer.Get();
        SymTypeFunc* t = new SymTypeFunc(type);
        symStack.Push(t->params);
        ParseParameterList();
        symStack.Pop();
        if (*lexer.Peek() == FIGURE_LEFT_BRACKET)
        {
            parseFunc = t;
            t->body = ParseBlock();
            //parseFunc = NULL;
        }
        result->SetType(t);
    }

    return result;
}

void Parser::ParseParameterList()
{
    while (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        SymType* type = ParseTypeSpecifier();
        Symbol* param = ParseDeclarator(type, true);

        Expected(*lexer.Peek() != EOF_, "expected a `)`");

        if (*lexer.Peek() == COMMA)
        {
            lexer.Get();
        }
        dynamic_cast<SymVar*>(param)->local = true;
        symStack.Add(param, 1);
    }

    lexer.Get();
}
