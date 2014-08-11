#pragma once

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "token.h"
using namespace std;

class Scanner
{
public:
    map <string, TokenType> keywords;
    map <string, TokenType> operators;
    map <char, string> escape_sequence;

    Scanner(const char*);
    ~Scanner();

    bool HasNext();
    BaseToken* Get();
    BaseToken* Next();

private:
    int curr_pos;
    int curr_line;
    BaseToken* curr_token;

    ifstream fin;

    void InitKeyWordsTable();
    void InitOperatorsTable();
    void InitEscapeSequencesTable();

    void GetWhiteSpace();
    bool GetSpace();
    bool GetComment();

    BaseToken* GetIdentificator();
    BaseToken* GetNumber();
    BaseToken* GetFloatNumber(string);
    BaseToken* GetChar();
    BaseToken* GetOperator();
    BaseToken* GetString();

    char GetCh();
    void UnGetCh();

    friend class SimpleParser;
    friend class Parser;
    friend class Lexer;
};