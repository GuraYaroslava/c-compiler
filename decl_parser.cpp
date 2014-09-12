#include "exception.h"
#include "_parser.h"

int counter = 0;

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
            SyntaxNode* left = new NodeVar(symbol);
            SyntaxNode* right = ParseExpression(precedences[COMMA]+1);
            NodeBinaryOp* node = new NodeBinaryOp(left, oper, right);
            nodeStack.push_back(node);
            node->GetType();
        }

        if (*lexer.Peek() == SEMICOLON)
        {
            lexer.Get();
            break;
        }

        if (*lexer.Peek() != COMMA)
        {
            Error("expected a `,`");
        }

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
        result = new SymTypeStruct(dummy, NULL);
    }
    else
    {
        BaseToken* name = lexer.Get();
        result = new SymTypeStruct(name, NULL);
    }

    //---------------------------------------------------------------------------
    result->fields = new SymTable();
    symStack.Push(result->fields);

    if (*lexer.Get() != FIGURE_LEFT_BRACKET)
    {
        Error("expected either a definition or a tag name");
    }

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
    //if (*lexer.Peek() != IDENTIFIER)
    //{
    //    Error("declaration does not declare anything");
    //}
    Symbol* declarator = ParseDeclarator(type);

    while (true)
    {
        symStack.Add(declarator);

        if (*lexer.Peek() == ASSIGN)
        {
            Error("data member initializer is not allowed");
        }

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
    //SymType* type = NULL;

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
        if (*lexer.Peek() != ROUND_RIGHT_BRACKET)
        {
            Error("expected a `)`");
        }
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
        if (*lexer.Peek() == SQUARE_RIGHT_BRACKET)
        {
            Error("unknown size");
        }

        SyntaxNode* index = ParseExpression();
        SymType* indexType = index->GetType();
        if (indexType != intType || !indexType->CanConvertTo(intType))
        {
            Error("expression must be an integral constant expression");
        }
        if (*index->token == IDENTIFIER)
        {
            Error("expression must have a constant value");
        }
        if (*lexer.Get() != SQUARE_RIGHT_BRACKET)
        {
            Error("exepcted a `]`");
        }
        int size = dynamic_cast<TokenVal <int> *>(index->token)->GetValue();
        result->SetType(new SymTypeArray(size, type));
    }
    else if (*token == ROUND_LEFT_BRACKET)
    {
        lexer.Get();
        SymTypeFunc* t = new SymTypeFunc(type);
        result->SetType(t);
        symStack.Push(t->params);
        ParseParameterList();
        symStack.Pop();
    }

    return result;
}

void Parser::ParseParameterList()
{
    int counter = 0;
    while (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        SymType* type = ParseTypeSpecifier();
        Symbol* param = ParseDeclarator(type, true);

        if (*lexer.Peek() == EOF_)
        {
            Error("expected a `)`");
        }

        if (*lexer.Peek() == COMMA)
        {
            lexer.Get();
        }

        symStack.Add(param);
    }

    lexer.Get();
}
