#pragma once

#include <map>
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

enum TokenType
{
    BOF_,
    EOF_,

    //tokens
    IDENTIFIER,
    CONSTANT,
    KEYWORD,
    OPERATOR,
    STRING,

    //token's separators
    COMMENT,
    NEWLINE,
    WHITESPACE,

    //constants
    CHARACTER,
    NUMBER_INT,
    NUMBER_FLOAT,

    //operators
    FIGURE_LEFT_BRACKET,
    FIGURE_RIGHT_BRACKET,
    ROUND_LEFT_BRACKET,
    ROUND_RIGHT_BRACKET,
    SQUARE_LEFT_BRACKET,
    SQUARE_RIGHT_BRACKET,

    ARROW,
    COMMA,
    POINT,
    SEMICOLON,

    ASSIGN,

    EQUAL,
    NOT_EQUAL,

    GREATER,
    LESS,

    GREATER_EQUAL,
    LESS_EQUAL,

    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULO,

    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN,

    //INCREASE,
    //DECREASE,
    //QUESTION,
    //COLON,

    NOT,
    AND,
    OR,

    BIT_AND,
    BIT_OR,
    BIT_XOR,
    BIT_NOT,
    BIT_SHIFT_LEFT,
    BIT_SHIFT_RIGHT,
    BIT_SHIFT_LEFT_ASSIGN,
    BIT_SHIFT_RIGHT_ASSIGN,
    BIT_AND_ASSIGN,
    BIT_XOR_ASSIGN,
    BIT_OR_ASSIGN,

    //keywords
    INT,
    FLOAT,
    CHAR,
    //VOID,

    DO,
    WHILE,
    IF,
    ELSE,
    FOR,

    BREAK,
    CONTINUE,
    RETURN,

    STRUCT,
};

class BaseToken
{
protected:
    string text;
    int line;
    int position;
    TokenType type;
    TokenType subType;

public:
    BaseToken();
    BaseToken(string, int, int, TokenType, TokenType);
    BaseToken(const BaseToken* token);
    ~BaseToken();

    map <TokenType, string> tokenTypeToString;

    string GetText();
    int GetLine();
    int GetPosition();
    TokenType GetType();
    TokenType GetSubType();

    bool operator == (TokenType);
    bool operator != (TokenType);

    void InitTokenTypeTable();
    virtual void Print(ostream& fout);
};

template <class Type>
class TokenVal: public BaseToken
{
private:
    Type value;

public:
    TokenVal(string text_, int pos_, int line_, TokenType type_, TokenType subType_, Type value_):
        BaseToken(text_, pos_, line_, type_, subType_)
    {
        value = value_;
    }

    virtual void Print(ostream& fout)
    {
        BaseToken::Print(fout);
        fout << "val: " << value << endl << endl;
    }
};

template <class Type>
Type GetValue(BaseToken *token)
{
    Type value_ = dynamic_cast <TokenVal <Type> *> (token)->value;
    return value_;
}