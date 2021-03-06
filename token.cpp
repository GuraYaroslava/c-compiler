#include "token.h"

BaseToken::BaseToken()
{
    text = "";
    line = 1;
    position = 1;
    type = BOF_;
    subType = BOF_;
    InitTokenTypeTable();
}

BaseToken::BaseToken(TokenType type_, TokenType subType_)
{
    text = "";
    line = 0;
    position = 0;
    type = type_;
    subType = subType_;
    InitTokenTypeTable();
}

BaseToken::BaseToken(string text_, int line_, int pos_, TokenType type_, TokenType subType_)
{
    text = text_;
    line = line_;
    position = pos_;
    type = type_;
    subType = subType_;
    InitTokenTypeTable();
}

BaseToken::BaseToken(const BaseToken* token_)
{
    text = token_->text;
    line = token_->line;
    position = token_->position;
    type = token_->type;
    subType = token_->subType;
    InitTokenTypeTable();
}

BaseToken::~BaseToken() {};

void BaseToken::SetText(string name)
{
    text = name;
}

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

TokenType BaseToken::GetSubType()
{
    return subType;
}

void BaseToken::Print(ostream &fout)
{
    fout << "type: " << tokenTypeToString[GetType()] << "        ";
    fout << "ln: " << GetLine() << "        ";
    fout << "pos: " << GetPosition() << "        ";
    fout << "lx: " << GetText() << "        ";
};

bool BaseToken::operator==(TokenType subType_)
{
    return subType == subType_ || type == subType_;
}

bool BaseToken::operator!=(TokenType subType_)
{
    return subType != subType_;
}

void BaseToken::InitTokenTypeTable()
{
    tokenTypeToString[EOF_] = "EOF";
    tokenTypeToString[BOF_] = "BOF";
    //tokens
    tokenTypeToString[IDENTIFIER] ="IDENTIFIER";
    tokenTypeToString[CONSTANT] ="CONSTANT";
    tokenTypeToString[KEYWORD] = "KEYWORD";
    tokenTypeToString[OPERATOR] = "OPERATOR";
    tokenTypeToString[STRING] = "STRING";
    //constants
    tokenTypeToString[NUMBER_INT] = "NUMBER_INT";
    tokenTypeToString[NUMBER_FLOAT] = "NUMBER_FLOAT";
    tokenTypeToString[CHARACTER] = "CHARACTER";
    //operators
    tokenTypeToString[FIGURE_LEFT_BRACKET] = "FIGURE_LEFT_BRACKET";
    tokenTypeToString[FIGURE_RIGHT_BRACKET] = "FIGURE_RIGHT_BRACKET";
    tokenTypeToString[ROUND_LEFT_BRACKET] = "ROUND_LEFT_BRACKET";
    tokenTypeToString[ROUND_RIGHT_BRACKET] = "ROUND_RIGHT_BRACKET";
    tokenTypeToString[SQUARE_LEFT_BRACKET] = "SQUARE_LEFT_BRACKET";
    tokenTypeToString[SQUARE_RIGHT_BRACKET] = "SQUARE_RIGHT_BRACKET";
    tokenTypeToString[ARROW] = "ARROW";
    tokenTypeToString[COMMA] = "COMMA";
    tokenTypeToString[POINT] = "POINT";
    tokenTypeToString[SEMICOLON] = "SEMICOLON";
    tokenTypeToString[ASSIGN] = "ASSIGN";
    tokenTypeToString[EQUAL] = "EQUAL";
    tokenTypeToString[NOT_EQUAL] = "NOT_EQUAL";
    tokenTypeToString[GREATER] = "GREATER";
    tokenTypeToString[LESS] = "LESS";
    tokenTypeToString[GREATER_EQUAL] = "GREATER_EQUAL";
    tokenTypeToString[LESS_EQUAL] = "LESS_EQUAL";
    tokenTypeToString[ADDITION] = "ADDITION";
    tokenTypeToString[SUBSTRACTION] = "SUBSTRACTION";
    tokenTypeToString[MULTIPLICATION] = "MULTIPLICATION";
    tokenTypeToString[DIVISION] = "DIVISION";
    tokenTypeToString[MODULO] = "MODULO";
    tokenTypeToString[ADD_ASSIGN] = "ADD_ASSIGN";
    tokenTypeToString[SUB_ASSIGN] = "SUB_ASSIGN";
    tokenTypeToString[MUL_ASSIGN] = "MULTI_ASSIGN";
    tokenTypeToString[DIV_ASSIGN] = "DIV_ASSIGN";
    tokenTypeToString[MOD_ASSIGN] = "MOD_ASSIGN";
    //tokenTypeToString[INCREASE] = "INCREASE";
    //tokenTypeToString[DECREASE] = "DECREASE";
    //tokenTypeToString[QUESTION] = "QUESTION";
    //tokenTypeToString[COLON] = "COLON";
    tokenTypeToString[NOT] = "NOT";
    tokenTypeToString[AND] = "AND";
    tokenTypeToString[OR] = "OR";
    tokenTypeToString[BIT_AND] = "BIT_AND";
    tokenTypeToString[BIT_OR] = "BIT_OR";
    tokenTypeToString[BIT_XOR] = "BIT_XOR";
    tokenTypeToString[BIT_NOT] = "BIT_NOT";
    tokenTypeToString[BIT_SHIFT_LEFT] = "BIT_SHIFT_LEFT";
    tokenTypeToString[BIT_SHIFT_RIGHT] = "BIT_SHIFT_RIGHT";
    tokenTypeToString[BIT_AND_ASSIGN] = "BIT_AND_ASSIGN";
    tokenTypeToString[BIT_OR_ASSIGN] = "BIT_OR_ASSIGN";
    tokenTypeToString[BIT_XOR_ASSIGN] = "BIT_XOR_ASSIGN";
    //keywords
    tokenTypeToString[INT] = "INT";
    tokenTypeToString[FLOAT] = "FLOAT";
    tokenTypeToString[CHAR] = "CHAR";
    tokenTypeToString[DO] = "DO";
    tokenTypeToString[WHILE] = "WHILE";
    tokenTypeToString[IF] = "IF";
    tokenTypeToString[ELSE] = "ELSE";
    tokenTypeToString[FOR] = "FOR";
    tokenTypeToString[BREAK] = "BREAK";
    tokenTypeToString[CONTINUE] = "CONTINUE";
    tokenTypeToString[RETURN] = "RETURN";
    tokenTypeToString[STRUCT] = "STRUCT";
    tokenTypeToString[PRINTF] = "PRINTF";
}