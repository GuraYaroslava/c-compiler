#include "exception.h"
#include "_parser.h"

void Parser::ParseDeclaration()
{
    //declaration-specifiers
    SymType* type = ParseTypeSpecifier();

    if (*lexer.Peek() == SEMICOLON)
    {
        //
    }
    else
    {
        //init-declarator-list
        ParseDeclarator();
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
        result = dynamic_cast <SymType*> (stack.Find(token->GetText()));
    }

    return result;
}

SymType* Parser::ParseStructSpecifier()
{

}

Symbol* Parser::ParseDeclarator()
{
    Symbol* result = NULL;
    SymType* type = NULL;

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
        result = ParseDeclarator();
        if (*lexer.Peek() != ROUND_RIGHT_BRACKET)
        {
            Error("expected a `)`");
        }
        lexer.Get();
    }

    if (*lexer.Peek() != IDENTIFIER)
    {
        Error("exepcted an identifier");
    }
    else if (stack.Find(lexer.Peek()->GetText()))
    {
        Error("redefinition");
    }

    result = new SymVar(lexer.Get());

	BaseToken* token = lexer.Peek();
	if (*token == SQUARE_LEFT_BRACKET)
	{
		type 
	}
	else if (*token == ROUND_LEFT_BRACKET)
	{

	}
}