#include "utils.h"
#include "scanner.h"
#include "exception.h"

Scanner::Scanner(const char* input)
{
    curr_pos = 0;
    curr_line = 1;
    curr_token = new BaseToken("BOF", curr_line, curr_pos, BOF_, BOF_);

    fin.open(input);

    InitKeyWordsTable();
    InitOperatorsTable();
    InitEscapeSequencesTable();
}

Scanner::~Scanner() {}

BaseToken* Scanner::Get()
{
    return curr_token;
}

BaseToken* Scanner::Next()
{
    GetWhiteSpace();

    char ch = fin.peek();
    if (fin.eof())
    {
        curr_token = new BaseToken("EOF", curr_line, ++curr_pos, EOF_, EOF_);
    }
    else if (isalpha_(ch))
    {
        curr_token = GetIdentificator();
    }
    else if (isdigit_(ch))
    {
        curr_token = GetNumber();
    }
    else if (operators[string(1, ch)])
    {
        curr_token = GetOperator();
    }
    else if (ch == '\'')
    {
        curr_token = GetChar();
    }
    else if (ch == '"')
    {
        curr_token = GetString();
    }
    else
    {
        throw Exception(curr_line, curr_pos, "unknown lexeme");
    }

    if (!curr_token)
    {
        Next();
    }

    return curr_token;
}

void Scanner::GetWhiteSpace()
{
    while (GetComment() || GetSpace()) {}
}

bool Scanner::GetSpace()
{
    bool result = false;
    while (fin.good() && isspace(fin.peek()))
    {
        GetCh();
        result = true;
    }
    return result;
}

bool Scanner::GetComment()
{
    bool result = false;
    if (fin.eof() || (fin.good() && fin.peek() != '/'))
    {
        return result;
    }
    GetCh();
    if (fin.peek() == '*')
    {
        do
        {
            GetCh();
            while (fin.good() && fin.peek() != '*')
            {
                GetCh();
            }
            GetCh();
        } while (fin.good() && fin.peek() != '/');
        if (fin.eof())
        {
            throw Exception(curr_line, curr_pos, "unexpected end of file found in comment");
        }
        GetCh();
        result = true;
    }
    else if (fin.peek() == '/')
    {
        char ch;
        while (fin.good() && (ch = fin.peek()) != '\n' && ch != EOF)
        {
            GetCh();
        }
        GetCh();
        result = true;
    }
    else
    {
        UnGetCh();
    }
    return result;
}

BaseToken* Scanner::GetIdentificator()
{
    string lexeme = "";
    for (char ch = fin.peek(); isalpha_(ch) || isdigit_(ch); ch = fin.peek())
    {
        lexeme += GetCh();
    }
    if (keywords[lexeme])
    {
        return new TokenVal <string> (lexeme, curr_line, curr_pos, KEYWORD, keywords[lexeme], lexeme);
    }
    return new TokenVal <string> (lexeme, curr_line, curr_pos, IDENTIFIER, IDENTIFIER, lexeme);
}

BaseToken* Scanner::GetNumber()
{
    int num, flag = 0;
    string lexeme = "";
    char ch = fin.peek();
    BaseToken* result = NULL;

    if (ch == '0')
    {
        lexeme += GetCh();
        ch = fin.peek();

        //hexadecimal
        if (ch == 'x' || ch == 'X')
        {
            lexeme += GetCh();
            for (char c = fin.peek();
                 isdigit_(c) || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
                 c = fin.peek())
            {
                lexeme += GetCh();
            }
            flag = 1;
            if (lexeme == "0x" || lexeme == "0X")
            {
                throw Exception(curr_line, curr_pos, "invalid hexadecimal number");
            }
        }

        //octal
        else
        {
            for (char c = fin.peek(); '0' <= c && c <= '7'; c = fin.peek())
            {
                lexeme += GetCh();
            }
            flag = 2;
            if (isdigit_(fin.peek()))
            {
                throw Exception(curr_line, curr_pos, "invalid octal number");
            }
        }
    }

    //decimal
    else
    {
        for (char c = fin.peek(); isdigit_(c); c = fin.peek())
        {
            lexeme += GetCh();
        }
        ch = fin.peek();
    }

    if (ch == '.' || ch == 'e' || ch == 'E')
    {
        return GetFloatNumber(lexeme);
    }

    char* ptr_start = &lexeme[0], *ptr_end;
    switch (flag)
    {
    case 0:
        num = strtol(ptr_start, &ptr_end, 10);
        break;
    case 1:
        num = strtol(ptr_start, &ptr_end, 16);
        break;
    case 2:
        num = strtol(ptr_start, &ptr_end, 8);
        break;
    }

    return new TokenVal <int> (lexeme, curr_line, curr_pos, CONSTANT, NUMBER_INT, num);
}

BaseToken* Scanner::GetFloatNumber(string lexeme)
{
    char ch, *ptr_start, *ptr_end;
    if (fin.peek() == '.')
    {
        lexeme += GetCh();
        for (char c = fin.peek(); isdigit_(c); c = fin.peek())
        {
            lexeme += GetCh();
        }
    }

    if ((ch = fin.peek()) == 'E' || ch == 'e')
    {
        lexeme += GetCh();

        if ((ch = fin.peek()) == '+' || ch == '-')
        {
            lexeme += GetCh();
        }
        int len = lexeme.length();
        for (char c = fin.peek(); isdigit_(c); c = fin.peek())
        {
            lexeme += GetCh();
        }

        if (len == lexeme.length())
        {
            throw Exception(curr_line, curr_pos, "invalid floating constant");
        }
    }
    ptr_start = &lexeme[0];
    float num = float(strtod(ptr_start, &ptr_end));
    if (+HUGE_VAL == num || num == -HUGE_VAL)
    {
        throw Exception(curr_line, curr_pos, "overflow or underflow occurred");
    }
    return new TokenVal <float> (lexeme, curr_line, curr_pos, CONSTANT, NUMBER_FLOAT, num);
}

BaseToken* Scanner::GetOperator()
{
    string oper = string(1, GetCh());
    char ch = fin.peek();
    if (oper == "." && isdigit_(ch))
    {
        UnGetCh();
        return GetFloatNumber("");
    }
    if (operators[oper+ch])
    {
        oper += GetCh();
        ch = fin.peek();
        if (operators[oper+ch])
        {
            oper += GetCh();
        }
    }
    return new TokenVal <string> (oper, curr_line, curr_pos, OPERATOR, operators[oper], oper);
}

BaseToken* Scanner::GetChar()
{
    GetCh();
    string value, lexeme = "\'";
    char ch = fin.peek();

    //escape-sequence
    if (ch == '\\')
    {
        lexeme += GetCh();
        ch = fin.peek();
        if (escape_sequence[ch] != "")
        {
            lexeme += GetCh();
        }
        if (escape_sequence[ch] == ""
           || (escape_sequence[ch] != "" && fin.peek() != '\''))
        {
            throw Exception(curr_line, curr_pos, "invalid escape sequence");
        }
        value = escape_sequence[ch];
    }
    else
    {
        if (ch != '\'' && ch != '\\' && ch != '\n' && ch != EOF)
        {
            lexeme += GetCh();
        }
        else
        {
            throw Exception(curr_line, curr_pos, "invalid character constant");
        }
        if (fin.peek() != '\'')
        {
            throw Exception(curr_line, curr_pos, "invalid character constant");
        }
        value = lexeme.substr(1, 1);
    }
    lexeme += "\'";
    GetCh();

    return new TokenVal <string> (lexeme, curr_line, curr_pos, CONSTANT, CHARACTER, value);
}

BaseToken* Scanner::GetString()
{
    bool escape = false;
    char ch = GetCh();
    string lexeme = "\"";
    string value = "";

    while (fin.good())
    {
        for (char c = fin.peek();
             c != '\"' && c != '\\' && c != '\n' && c != EOF;
             c = fin.peek())
        {
            ch = GetCh();
            value += ch;
            lexeme += ch;
        }

        if (fin.peek() == '\\')
        {
            ch = GetCh();
            lexeme += ch;

            if (escape_sequence[fin.peek()] == "")
            {
                throw Exception(curr_line, curr_pos, "invalid string literal");
            }
            value += escape_sequence[fin.peek()];
            lexeme += GetCh();
        }
        else if (fin.peek() == '"')
        {
            GetCh();
            lexeme += "\"";
            break;
        }
        else
        {
            throw Exception(curr_line, curr_pos, "missing closing quote");
        }
    }

    return new TokenVal<string> (lexeme, curr_line, curr_pos, STRING, STRING, value);
}

void Scanner::InitEscapeSequencesTable()
{
    escape_sequence['\''] = "\'";
    escape_sequence['"'] = "\"";
    escape_sequence['?'] = "\?";
    escape_sequence['\\'] = "\\";
    escape_sequence['a'] = "\a";
    escape_sequence['b'] = "\b";
    escape_sequence['f'] = "\f";
    escape_sequence['n'] = "\n";
    escape_sequence['r'] = "\r";
    escape_sequence['t'] = "\t";
    escape_sequence['v'] = "\v";
}

void Scanner::InitOperatorsTable()
{
    operators["{"] = FIGURE_LEFT_BRACKET;
    operators["}"] = FIGURE_RIGHT_BRACKET;
    operators["("] = ROUND_LEFT_BRACKET;
    operators[")"] = ROUND_RIGHT_BRACKET;
    operators["["] = SQUARE_LEFT_BRACKET;
    operators["]"] = SQUARE_RIGHT_BRACKET;
    operators["->"] = ARROW;
    operators[","] = COMMA;
    operators["."] = POINT;
    operators[";"] = SEMICOLON;
    operators["="] = ASSIGN;
    operators["=="] = EQUAL;
    operators["!="] = NOT_EQUAL;
    operators[">"] = GREATER;
    operators["<"] = LESS;
    operators[">="] = GREATER_EQUAL;
    operators["<="] = LESS_EQUAL;
    operators["+"] = ADDITION;
    operators["-"] = SUBSTRACTION;
    operators["*"] = MULTIPLICATION;
    operators["/"] = DIVISION;
    operators["%"] = MODULO;
    operators["+="] = ADD_ASSIGN;
    operators["-="] = SUB_ASSIGN;
    operators["*="] = MUL_ASSIGN;
    operators["/="] = DIV_ASSIGN;
    operators["%="] = MOD_ASSIGN;
    //operators["++"] = INCREASE;
    //operators["--"] = DECREASE;
    //operators["?"] = QUESTION;
    //operators[":"] = COLON;
    operators["!"] = NOT;
    operators["&&"] = AND;
    operators["||"] = OR;
    operators["&"] = BIT_AND;
    operators["|"] =  BIT_OR;
    operators["^"] = BIT_XOR;
    operators["~"] = BIT_NOT;
    operators[">>"] = BIT_SHIFT_RIGHT;
    operators["<<"] = BIT_SHIFT_LEFT;
    operators[">>="] = BIT_SHIFT_RIGHT_ASSIGN;
    operators["<<="] = BIT_SHIFT_LEFT_ASSIGN;
    operators["&="] = BIT_AND_ASSIGN;
    operators["|="] = BIT_OR_ASSIGN;
    operators["^="] = BIT_XOR_ASSIGN;
}

void Scanner::InitKeyWordsTable()
{
    keywords["int"] = INT;
    keywords["float"] =FLOAT;
    keywords["char"] = CHAR;
    keywords["do"] = DO;
    keywords["while"] = WHILE;
    keywords["if"] = IF;
    keywords["else"] = ELSE;
    keywords["for"] = FOR;
    keywords["break"] = BREAK;
    keywords["continue"] = CONTINUE;
    keywords["return"] = RETURN;
    keywords["struct"] = STRUCT;
}

char Scanner::GetCh()
{
    char ch = fin.get();
    if (ch == '\n')
    {
        curr_line++;
        curr_pos = 0;
    }
    else
    {
        curr_pos++;
    }
    return ch;
}

void Scanner::UnGetCh()
{
    fin.unget();
    if (--curr_pos < 0)
    {
        curr_pos = 0;
    }
}