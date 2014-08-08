#include <string>
#include <iomanip>
#include <sstream>
#include "token.h"

BaseToken::BaseToken()//: text(""), line(0), position(0), type(LX_BOF) {InitTokenNameTable();};
{
    text = "";
    line = 0;
    position = 0;
    type = LX_BOF;
    InitTokenNameTable();
}

BaseToken::BaseToken(string text_, int line_, int pos_, TokenType type_)
{
    text = text_;
    line = line_;
    position = pos_;
    type = type_;
    InitTokenNameTable();
}

BaseToken::BaseToken(const BaseToken* token_)
{
    text = token_->text;
    line = token_->line;
    position = token_->position;
    type = token_->type;
    InitTokenNameTable();
}

BaseToken::~BaseToken() {};

string BaseToken::GetText()
{
    return text;
}

int BaseToken::GetLine()
{
    return line;
}

int BaseToken::GetPosition()
{
    return position;
}

TokenType BaseToken::GetType()
{
    return type;
}

void BaseToken::Print(ostream &fout)
{
    fout << setw(20) << token_name[GetType()] << "\t";
    fout << setw(10) << GetLine() << "\t";
    fout << setw(10) << GetPosition() + 1 << "\t";
    fout << setw(10) << GetText() << "\t";
};

bool BaseToken::IsOperand()
{
    return type == NUMBER_INT || type == NUMBER_DOUBLE || type == IDENTIFIER;
}

bool BaseToken::operator == (TokenType t_token)
{
    return type == t_token;
}

bool BaseToken::operator != (TokenType t_token)
{
    return type != t_token;
}

void BaseToken::InitTokenNameTable()
{
    token_name[KEY_WORD] = "KEY_WORD";
    token_name[OPERATOR] = "OPERATOR";
    token_name[SEPARATOR] = "SEPARATOR";
    token_name[NUMBER_INT] = "NUMBER_INT";
    token_name[NUMBER_DOUBLE] = "NUMBER_DOUBLE";
    token_name[IDENTIFIER] ="IDENTIFIER";
    token_name[STRING] = "STRING";
    token_name[LX_EOF] = "EOF";
    token_name[LX_BOF] = "BOF";

    //SEPARATORS
    token_name[ROUND_LEFT_BRACKET] = "ROUND_LEFT_BRACKET";
    token_name[ROUND_RIGHT_BRACKET] = "ROUND_RIGHT_BRACKET";
    token_name[SQUARE_LEFT_BRACKET] = "SQUARE_LEFT_BRACKET";
    token_name[SQUARE_RIGHT_BRACKET] = "SQUARE_RIGHT_BRACKET";
    token_name[FIGURE_LEFT_BRACKET] = "FIGURE_LEFT_BRACKET";
    token_name[FIGURE_RIGHT_BRACKET] = "FIGURE_RIGHT_BRACKET";
    token_name[SEMICOLON] = "SEMICOLON";
    token_name[COMMA] = "COMMA";

    //OPERATORS
    token_name[ASSIGN] = "ASSIGN";
    token_name[EQUAL] = "EQUAL";
    token_name[NOT_EQUAL] = "NOT_EQUAL";
    token_name[GREATER] = "GREATER";
    token_name[LESS] = "LESS";
    token_name[GREATER_EQUAL] = "GREATER_EQUAL";
    token_name[LESS_EQUAL] = "LESS_EQUAL";

    token_name[ADDITION] = "ADDITION";
    token_name[SUBSTRACTION] = "SUBSTRACTION";
    token_name[MULTIPLICATION] = "MULTIPLICATION";
    token_name[DIVISION] = "DIVISION";
    token_name[MODULO] = "MODULO";

    token_name[ADD_ASSIGN] = "ADD_ASSIGN";
    token_name[SUB_ASSIGN] = "SUB_ASSIGN";
    token_name[MUL_ASSIGN] = "MULTI_ASSIGN";
    token_name[DIV_ASSIGN] = "DIV_ASSIGN";
    token_name[MOD_ASSIGN] = "MOD_ASSIGN";

    token_name[INCREASE] = "INCREASE";
    token_name[DECREASE] = "DECREASE";

    token_name[NOT] = "NOT";
    token_name[AND] = "AND";
    token_name[OR] = "OR";
        
    token_name[QUESTION] = "QUESTION";
    token_name[COLON] = "COLON";
    token_name[OR] = "OR";

    token_name[BIT_AND] = "BIT_AND";
    token_name[BIT_OR] = "BIT_OR";
    token_name[BIT_XOR] = "BIT_XOR";
    token_name[BIT_NOT] = "BIT_NOT";
    token_name[BIT_SHIFT_LEFT] = "BIT_SHIFT_LEFT";
    token_name[BIT_SHIFT_RIGHT] = "BIT_SHIFT_RIGHT";
    token_name[BIT_AND_ASSIGN] = "BIT_AND_ASSIGN";
    token_name[BIT_OR_ASSIGN] = "BIT_OR_ASSIGN";
    token_name[BIT_XOR_ASSIGN] = "BIT_XOR_ASSIGN";

    token_name[ARROW] = "ARROW";
    token_name[POINT] = "POINT";

    //KEY_WORDS
    token_name[CONST] = "CONST";
    token_name[INT] = "INT";
    token_name[DOUBLE] = "DOUBLE";
    token_name[CHAR] = "CHAR";

    token_name[DO] = "DO";
    token_name[WHILE] = "WHILE";
    token_name[IF] = "IF";
    token_name[ELSE] = "ELSE";
    token_name[FOR] = "FOR";

    token_name[BREAK] = "BREAK";
    token_name[CONTINUE] = "CONTINUE";
    token_name[RETURN] = "RETURN";

    token_name[STRUCT] = "STRUCT";
}