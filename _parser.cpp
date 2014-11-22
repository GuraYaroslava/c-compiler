#include "_parser.h"
#include "exception.h"

Parser::Parser(const char* fin, const char* asmout):
    lexer(fin),
    generator(asmout),
    parseFunc(NULL),
    parseIter(NULL),
    counter(0)
{
    Init();
}

Parser::~Parser() {}

void Parser::SetUnUsed(const string& name)
{
    symStack.SetUnUsed(name);
}

void Parser::PushLocals(SymTable* locals)
{
    symStack.Push(locals);
}

void Parser::PopLocals()
{
    symStack.Pop();
}

bool Parser::Eof()
{
    return *lexer.Peek() == EOF_ ? true : false;
}

void Parser::Next()
{
    if (*lexer.Peek() == SEMICOLON)
    {
        lexer.Get();
    }
}

void Parser::Error(const char* msg)
{
    throw Exception(lexer.GetLine(), lexer.GetPos(), msg);
}

void Parser::Error(const string msg)
{
    throw Exception(lexer.GetLine(), lexer.GetPos(), msg);
}

void Parser::Expected(TokenType actual, TokenType expected)
{
    BaseToken* t = new BaseToken();
    if (actual != expected)
    {
        Error("expected a " + t->tokenTypeToString[expected]);
    }
}

void Parser::Expected(bool actual, const char* msg)
{
    bool expected = true;
    if (actual != expected)
    {
        Error(msg);
    }
}

void Parser::Init()
{
    SymTable* predefined = new SymTable();
    predefined->Add(intType);
    predefined->Add(floatType);
    predefined->Add(charType);
    symStack.Push(predefined);
    symStack.Push(new SymTable());

    precedences[BOF_] = INF;
    precedences[EOF_] = INF;

    precedences[COMMA] = 1;

    precedences[ASSIGN] = 2;
    precedences[ADD_ASSIGN] = 2;
    precedences[SUB_ASSIGN] = 2;
    precedences[MUL_ASSIGN] = 2;
    precedences[DIV_ASSIGN] = 2;
    precedences[MOD_ASSIGN] = 2;
    precedences[BIT_SHIFT_LEFT_ASSIGN] = 2;
    precedences[BIT_SHIFT_RIGHT_ASSIGN] = 2;
    precedences[BIT_AND_ASSIGN] = 2;
    precedences[BIT_XOR_ASSIGN] = 2;
    precedences[BIT_OR_ASSIGN] = 2;

    precedences[OR] = 3;
    precedences[AND] = 4;

    precedences[BIT_OR] = 5;
    precedences[BIT_XOR] = 6;
    precedences[BIT_AND] = 7;

    precedences[EQUAL] = 8;
    precedences[NOT_EQUAL] = 8;

    precedences[LESS] = 9;
    precedences[GREATER] = 9;
    precedences[LESS_EQUAL] = 9;
    precedences[GREATER_EQUAL] = 9;

    precedences[BIT_SHIFT_LEFT] = 10;
    precedences[BIT_SHIFT_RIGHT] = 10;

    precedences[SUBSTRACTION] = 11;
    precedences[ADDITION] = 11;

    precedences[MULTIPLICATION] = 12;
    precedences[DIVISION] = 12;
    precedences[MODULO] = 12;

    //UNARY operator precedence = 13
    unary_oper[NOT] = true;
    unary_oper[BIT_NOT] = true;
    unary_oper[BIT_AND] = true;// address of an object

    unary_oper[ADDITION] = true;
    unary_oper[SUBSTRACTION] = true;
    unary_oper[MULTIPLICATION] = true;// indirection through a pointer

    precedences[SEMICOLON] = INF;

    //POSTFIX
    precedences[ARROW] = 14;
    precedences[POINT] = 14;

    precedences[ROUND_LEFT_BRACKET] = 14;
    precedences[ROUND_RIGHT_BRACKET] = INF;

    precedences[SQUARE_LEFT_BRACKET] = 14;
    precedences[SQUARE_RIGHT_BRACKET] = INF;

    //Associativity
    right_assoc_oper[NOT] = true;
    right_assoc_oper[BIT_NOT] = true;
    //right_assoc_oper[ADDITION] = true;//unary
    //right_assoc_oper[SUBSTRACTION] = true;//unary
    right_assoc_oper[MULTIPLICATION] = true;

    right_assoc_oper[ASSIGN] = true;
    right_assoc_oper[ADD_ASSIGN] = true;
    right_assoc_oper[SUB_ASSIGN] = true;
    right_assoc_oper[MUL_ASSIGN] = true;
    right_assoc_oper[DIV_ASSIGN] = true;
    right_assoc_oper[MOD_ASSIGN] = true;

    right_assoc_oper[BIT_AND_ASSIGN] = true;
    right_assoc_oper[BIT_XOR_ASSIGN] = true;
    right_assoc_oper[BIT_OR_ASSIGN] = true;
    right_assoc_oper[BIT_SHIFT_LEFT_ASSIGN] = true;
    right_assoc_oper[BIT_SHIFT_RIGHT_ASSIGN] = true;
}
