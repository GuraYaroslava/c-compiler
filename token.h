#ifndef TOKEN_H
#define TOKEN_H

#include <map>
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

enum TokenType
{
    DEFAULT,
    LX_BOF,
    LX_EOF,
    SPACE,
    NEWLINE,
    KEY_WORD,
    OPERATOR,
    SEPARATOR,
    NUMBER_INT,
    NUMBER_DOUBLE,
    STRING,
    IDENTIFIER,
    COMMENT,
    UNKNOWN,

    //SEPARATORS
    ROUND_LEFT_BRACKET,
    ROUND_RIGHT_BRACKET,
    SQUARE_LEFT_BRACKET,
    SQUARE_RIGHT_BRACKET,
    FIGURE_LEFT_BRACKET,
    FIGURE_RIGHT_BRACKET,
    SEMICOLON,
    COMMA,

    //OPERATORS
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

    INCREASE,
    DECREASE,

    NOT,
    AND,
    OR,

    QUESTION,
    COLON,

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

    ARROW,
    POINT,

    //KEY_WORDS
    CONST,
    INT,
    DOUBLE,
    CHAR,

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

public:
    BaseToken();
    BaseToken(string, int, int, TokenType);
    BaseToken(const BaseToken *token);
    ~BaseToken();

    map <TokenType, string> token_name;

    int GetLine();
    int GetPosition();
    string GetText();
    TokenType GetType();

    bool IsOperand();
    void InitTokenNameTable();
    virtual void Print(ostream &fout);
    bool operator == (TokenType);
    bool operator != (TokenType);
};

template <class Type>
class TokenVal: public BaseToken
{
public:
    Type value;

    TokenVal(string text_, int pos_, int line_, TokenType type_, Type value_): BaseToken(text_, pos_, line_, type_), value(value_) {};
    //{
    //    BaseToken(text_, pos_, line_, type_);
    //    value = value_;
    //}
    virtual void Print(ostream &fout)
    {
        BaseToken::Print(fout);
        fout << setw(10) << value << endl;
    }
};

template <class Type>
Type GetValue(BaseToken *token)
{
    Type value_ = dynamic_cast <TokenVal <Type> *> (token)->value;
    return value_;
}

#endif TOKEN_H