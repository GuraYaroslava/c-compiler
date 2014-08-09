#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include "token.h"
#include "scanner.h"
#include "exception.h"

Scanner::Scanner(const char *input): fin(input), curr_token(new BaseToken("", curr_line, curr_pos, BOF_))
{
    curr_pos = 0;
    curr_line = 1;
    getline(fin, curr_str);
    InitKeyWordsTable();
    InitOperationsTable();
    InitSeparatorsTable();
    InitEscapeSequencesTable();
}

Scanner::~Scanner()
{
    //delete curr_token;
    //curr_token = NULL;
}

BaseToken* Scanner::Get()
{
    return curr_token;
}

BaseToken* Scanner::Next()
{
    char ch = curr_str[curr_pos];

    while (isspace(ch))
    {
        ch = curr_str[++curr_pos];
    }

    if (ch == '\0' || ch == '\n')
    {
        curr_token = NewLine();
        if (*curr_token != EOF_) Next();
    }
    else if (ch == '/')
        curr_token = GetComment();
    else if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ch == '_')
        curr_token = GetIdentificator(ch);
    else if (isdigit(ch) /*|| ch == '.'*/)    //.5=0.5
        curr_token = GetNumber(ch);
    else if (separator[ch])
        curr_token = GetSeparator(ch);
    else if (operation[string(1, ch)])
        curr_token = GetOperation(ch);
    else if (ch == '\'')
        curr_token = GetChar();
    else if (ch == '"')
        curr_token = GetString();
    else 
        curr_token = new BaseToken(string(ch, 1), curr_line, ++curr_pos, UNKNOWN);
    return curr_token;
}

bool Scanner::HasNext()
{
    return curr_token->GetType() != EOF_;
}

BaseToken* Scanner::NewLine()
{
    if (fin.eof()) return new BaseToken("EOF", curr_line, curr_pos, EOF_);
    getline(fin, curr_str);
    return new BaseToken("", ++curr_line, curr_pos = 0, NEWLINE);
}

BaseToken* Scanner::GetIdentificator(char ch)
{
    string lexeme = "";
    BaseToken token;
    do 
    { 
        lexeme += ch;
        ch = curr_str [++curr_pos];
    } while ((('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ch == '_') || isdigit(ch));
    //TokenType t_token = (key_word[lexeme]) ? KEY_WORD : IDENTIFIER;
    //string v_token = (key_word[lexeme]) ? token.tokenTypeToString [key_word[lexeme]] : lexeme;
    //return new TokenVal<string> (lexeme, curr_line, curr_pos, t_token, v_token);
    if (key_word[lexeme]) return new TokenVal<TokenType> (lexeme, curr_line, curr_pos, key_word[lexeme], key_word[lexeme]);
    else return new TokenVal <string> (lexeme, curr_line, curr_pos, IDENTIFIER, lexeme);
}

BaseToken* Scanner::GetNumber(char ch)
{
    enum State {DIGIT, AFTER_POINT, AFTER_E, AFTER_OPER};
    char *ptr_start =  &curr_str[curr_pos], *ptr_end;
    string lexeme = "";
    TokenType t_token;
    State state;    
    if (ch == '0' && ('x' == curr_str[curr_pos+1] || curr_str[curr_pos+1] == 'X'))
    {
        t_token = NUMBER_INT;
        lexeme = "0x";
        ch = curr_str[curr_pos+=2];
        while (('A' <= ch && ch <= 'F') || ('a' <= ch && ch <= 'f') || isdigit(ch))
        {
            lexeme += ch;
            ch = curr_str[++curr_pos];
        }
        if (lexeme == "0x")
            throw Exception(curr_line, curr_pos, "Invalid hexadecimal number.");
        int num = strtol(ptr_start, &ptr_end, 16);
        if (LONG_MAX == num || num ==  LONG_MIN) 
            throw Exception(curr_line, curr_pos, "Overflow or underflow occurred.");
        return new TokenVal <int> (lexeme, curr_line, curr_pos, t_token, num);
    }    
    else if (ch == '0' && ('.' != curr_str[curr_pos+1]))
    {
        t_token = NUMBER_INT;
        while ('0' <= ch && ch <= '7')
        {
            lexeme += ch;
            ch = curr_str[++curr_pos];
        }
        if (isdigit(ch))
            throw Exception(curr_line, curr_pos, "Invalid octal number.");
        int num =  strtol(ptr_start, &ptr_end, 8);
        if (LONG_MAX == num || num ==  LONG_MIN)
            throw Exception(curr_line, curr_pos, "Overflow or underflow occurred.");
        return new TokenVal <int> (lexeme, curr_line, curr_pos, t_token, num);
    }
    else
    {
        bool loop = true;
        while (loop)
        {
            if (isdigit(ch)) state = DIGIT;
            else if (ch == '.') state = AFTER_POINT;
            else if ('e' == ch || ch == 'E') state = AFTER_E;
            else if ('-' == ch || ch == '+') state = AFTER_OPER;
            else {loop = false; continue;}
            
            switch (state)
            {
                case DIGIT:
                    t_token = NUMBER_INT;
                    do
                    {
                        lexeme += ch; 
                        ch = curr_str[++curr_pos];
                    } while (isdigit(ch));
                    break;
                case AFTER_POINT:
                    t_token = NUMBER_FLOAT;
                    //if (!isdigit(curr_str[curr_pos+1])) throw Exception(curr_line, curr_pos, "More than one symbol \".\" in the number.");
                    do 
                    {
                        lexeme += ch; 
                        ch = curr_str[++curr_pos];
                    } while (isdigit(ch));
                    if (ch == '.') throw Exception(curr_line, curr_pos, "More than one symbol \".\" in the number.");
                    break;
                case AFTER_E:
                    t_token = NUMBER_FLOAT;
                    lexeme += ch;
                    ch = curr_str[++curr_pos];
                    if (isdigit(ch))
                    {
                        do
                        {
                            lexeme += ch; 
                            ch = curr_str[++curr_pos];
                        } while (isdigit(ch));
                        loop = false;
                    }
                    else if ('-' != ch && ch != '+')
                        throw Exception(curr_line, curr_pos, "Invalid symbol \""+string(1, ch)+"\" in the real number.");
                    break;
                case AFTER_OPER:
                    if ('e' != curr_str[curr_pos-1] && curr_str[curr_pos-1] != 'E')
                    {
                        loop = false;
                        break;
                    }
                    if (!isdigit(curr_str[curr_pos+1])) 
                        throw Exception(curr_line, curr_pos, "Invalid symbol \""+string(1, ch)+"\" in the real number.");
                    do
                    {
                        lexeme += ch; 
                        ch = curr_str[++curr_pos];
                    } while (isdigit(ch));
                    break;
                default: throw Exception(curr_line, curr_pos, "Invalid number.");
            }
        }
        double num = strtod(ptr_start, &ptr_end);
        if (+HUGE_VAL == num || num == -HUGE_VAL)
            throw Exception(curr_line, curr_pos, "Overflow or underflow occurred.");
        return new TokenVal <double> (lexeme, curr_line, curr_pos, t_token, num);
    }
}

BaseToken* Scanner::GetSeparator(char curr_ch)
{
    BaseToken token;
    return new TokenVal <TokenType> (string(1, curr_ch), curr_line, curr_pos++, separator[curr_ch], separator[curr_ch]);
}

BaseToken* Scanner::GetOperation(char curr_ch) 
{
    BaseToken token;
    string oper = string(1, curr_ch);
    char n_ch = curr_str[++curr_pos];
    if (!isspace(n_ch) && n_ch != '\0') 
        if (operation[oper+n_ch])
        {
            oper += n_ch;
            ++curr_pos;
        }
        return new TokenVal <TokenType> (oper, curr_line, curr_pos, operation[oper], operation[oper]);
}

BaseToken* Scanner::GetComment()
{
    char ch = curr_str[++curr_pos];
    if (ch == '*')
    {
        do 
        { 
            if (ch == '\0') 
            {
                if (NewLine()->GetType() == EOF_) 
                    throw Exception(curr_line, curr_pos, "Unfinished comment.");
                ch = curr_str[curr_pos];
                continue;
            }
            ch = curr_str[++curr_pos];
        } while (ch != '*' || (curr_str[curr_pos+1] != '/'));
        curr_pos += 2;
        return new BaseToken("", curr_line, curr_pos, COMMENT);
    }
    else if (ch == '/') return NewLine();
    else return GetOperation(curr_str[--curr_pos]);
}

BaseToken* Scanner::GetChar()
{
    string lexeme = "";
    string text = "'";
    char ch;
    text += (ch = curr_str[++curr_pos]);
    if (ch == '\0') 
        throw Exception(curr_line, curr_pos, "New line in character constant.");
    if (ch == '\'') 
        throw Exception(curr_line, curr_pos, "Empty character constant.");
    if (ch == '\\')
    {
        text += (ch = curr_str[++curr_pos]);
        if (escape_sequence[ch])
            lexeme += escape_sequence[ch];
        else throw Exception(curr_line, curr_pos, "Invalid escape sequence: \""+lexeme+"\"");
    }
    else 
        lexeme += ch;
    if (curr_str[++curr_pos] == '\'')
        return new TokenVal<string> (text+'\'', curr_line, curr_pos++, CHAR, lexeme);
    else 
        throw Exception(curr_line, curr_pos, "Too long character constant.");
}

BaseToken* Scanner::GetString()
{
    string lexeme = "";
    string text = "\"";
    char ch;
    text += (ch = curr_str[++curr_pos]);
    while (ch != '"')
    {
        if (ch == '\\') 
        {
            text += (ch = curr_str[++curr_pos]);
            if (escape_sequence[ch])
                lexeme += escape_sequence[ch];
            else 
                lexeme += '\\';
            text += (ch = curr_str[++curr_pos]);
            continue;
        }
        if (ch == '\0')
        {
            if (NewLine()->GetType() == EOF_)
                throw Exception(curr_line, curr_pos, "Unfinished string.");
            lexeme += '\n';
            text += '\n';
            text += (ch = curr_str[curr_pos]);
            continue;
        }
        lexeme += ch;
        text += (ch = curr_str[++curr_pos]);
    }
    return new TokenVal<string> (text, curr_line, curr_pos++, STRING, lexeme);
}

void Scanner::InitEscapeSequencesTable()
{
    escape_sequence['n'] = '\n';
    escape_sequence['t'] = '\t';
    escape_sequence['v'] = '\v';
    escape_sequence['b'] = '\b';
    escape_sequence['r'] = '\r';
    escape_sequence['f'] = '\f';
    escape_sequence['\''] = '"';
    escape_sequence['"'] = '\"';
    escape_sequence['\\'] = '\\';
}

void Scanner::InitSeparatorsTable()
{
    separator['('] = ROUND_LEFT_BRACKET;
    separator[')'] = ROUND_RIGHT_BRACKET;
    separator['['] = SQUARE_LEFT_BRACKET;
    separator[']'] = SQUARE_RIGHT_BRACKET;
    separator['{'] = FIGURE_LEFT_BRACKET;
    separator['}'] = FIGURE_RIGHT_BRACKET;
    separator[';'] = SEMICOLON;
    separator[','] = COMMA;
}

void Scanner::InitOperationsTable()
{
    operation["="] =  ASSIGN;

    operation["=="] = EQUAL;
    operation["!="] = NOT_EQUAL;

    operation[">"] =  GREATER;
    operation["<"] =  LESS;
    operation[">="] = GREATER_EQUAL;
    operation["<="] = LESS_EQUAL;

    operation["+"] =  ADDITION;
    operation["-"] =  SUBSTRACTION;

    operation["*"] =  MULTIPLICATION;
    operation["/"] =  DIVISION;
    operation["%"] =  MODULO;

    operation["+="] = ADD_ASSIGN;
    operation["-="] = SUB_ASSIGN;
    operation["*="] = MUL_ASSIGN;
    operation["/="] = DIV_ASSIGN;
    operation["%="] = MOD_ASSIGN;

    operation["++"] = INCREASE;
    operation["--"] = DECREASE;

    operation["!"] =  NOT;
    operation["&&"] = AND;
    operation["||"] = OR;

    operation["?"] =  QUESTION;
    operation[":"] =  COLON;

    operation["&"] =  BIT_AND;
    operation["|"] =  BIT_OR;
    operation["^"] =  BIT_XOR;
    operation["~"] =  BIT_NOT;

    operation[">>"] = BIT_SHIFT_RIGHT;
    operation["<<"] = BIT_SHIFT_LEFT;

    operation[">>="] = BIT_SHIFT_RIGHT_ASSIGN;
    operation["<<="] = BIT_SHIFT_LEFT_ASSIGN;
    operation["&="] = BIT_AND_ASSIGN;
    operation["|="] = BIT_OR_ASSIGN;
    operation["^="] = BIT_XOR_ASSIGN;

    operation["->"] = ARROW;
    operation["."] =  POINT;
}

void Scanner::InitKeyWordsTable()
{
    key_word["const"] = CONST;
    key_word["int"] = INT;
    key_word["double"] = DOUBLE;
    key_word["char"] = CHAR;

    key_word["do"] = DO;
    key_word["while"] = WHILE;
    key_word["else"] = ELSE;
    key_word["if"] = IF;
    key_word["for"] = FOR;

    key_word["break"] = BREAK;
    key_word["continue"] = CONTINUE;
    key_word["return"] = RETURN;

    key_word["struct"] = STRUCT;
}