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
    Scanner(const char*);
    ~Scanner();

    bool HasNext();
    BaseToken* Get();
    BaseToken* Next();

private:
    map <string, TokenType> key_word;
    map <string, TokenType> operation;
    map <char, TokenType> separator;
    map <char, char> escape_sequence;
        
    void InitKeyWordsTable();
    void InitOperationsTable();
    void InitSeparatorsTable();
    void InitEscapeSequencesTable();

    BaseToken* NewLine();
    BaseToken* GetIdentificator(char);
    BaseToken* GetNumber(char); 
    BaseToken* GetSeparator(char);
    BaseToken* GetOperation(char);
    BaseToken* GetComment();
    BaseToken* GetChar();
    BaseToken* GetString();

    int curr_pos;
    int curr_line;
    BaseToken* curr_token;
    string curr_str;
    ifstream fin;

    friend class SimpleParser;
    friend class Parser;
    friend class Lexer;
};