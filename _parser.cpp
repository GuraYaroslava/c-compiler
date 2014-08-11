#include <sstream>
#include <ostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "exception.h"
#include "_parser.h"

#define POSTFIX 16
#define PREFIX 15
#define UNARY 15
#define MAX 17

SyntaxNode* Parser::ParseExpression(int priority)
{
    if (priority == PREFIX)
    {
        BaseToken* oper = lexer.Peek();
        if (unary_oper[oper->GetType()])
        {
            lexer.Get();
            SyntaxNode *expr = ParseExpression(priority+1);
            if (!expr) Error("[UnaryOp->GetType()]");
            return new NodeUnaryOp(oper, expr);
        }
    }

    if (priority == MAX) return ParseFactor();

    SyntaxNode *left = ParseExpression(priority+1);
    if (!left) return left;

    BaseToken* oper = lexer.Peek();
    TokenType t_oper = oper->GetType();

    while (priority_table[t_oper] == priority)
    {
        lexer.Get();
        if (priority == POSTFIX)
        {
            if (*oper == SQUARE_LEFT_BRACKET)
            {
                if (*lexer.Peek() == SQUARE_RIGHT_BRACKET)
                    Error("Missing expression in square brackets.");
                left = new NodeBinaryOp(left, oper, ParseExpression(0));
                if (*lexer.Get() != SQUARE_RIGHT_BRACKET)
                    Error("Missing close square right bracket.");
            }
            if (t_oper == ROUND_LEFT_BRACKET)
                ParseFuncCall(left, oper);
            if (t_oper == POINT || t_oper == ARROW)
            {
                if (*lexer.Peek() != IDENTIFIER)
                    Error("Identifier is required after selecting element.");
                Symbol* s = stack->Find(left->token->GetText());
                if (!s) Error("Ne syshectbuet!!!");
                SyntaxNode *field = ParseExpression(priority+1);
                //существует такое поле или нет, проверим, когда типы сравнивать можно будет
                left = new NodeRecordAccess(left, oper, field);
                dynamic_cast <NodeRecordAccess*>(left)->symbol = dynamic_cast <SymVar*> (s);
            }
            //if (t_oper == INCREASE || t_oper == DECREASE)
            //    left = new NodeBinaryOp(left, oper, NULL);
        }
        else
        {
            SyntaxNode *right = ParseExpression(priority + (right_assoc_oper[t_oper] == true ? 0 : 1));
            if (right == NULL)
                Error("Missing operand. [ParseExpression]");
            left = new NodeBinaryOp(left, oper, right);
        }
        oper = lexer.Peek();
        t_oper = oper->GetType();
    }
    return left;
};

SyntaxNode* Parser::ParseFactor()
{
    Symbol* s = NULL;
    BaseToken* token = lexer.Peek();
    SyntaxNode *res = new NodeVar(token);
    TokenType t_token = token->GetType();
    if (t_token == EOF_)
        Error("Invalid expression.");
    if (t_token != SEMICOLON && t_token != ROUND_RIGHT_BRACKET) lexer.Get();
    if (t_token == ROUND_LEFT_BRACKET)
    {
        if (*lexer.Peek() == ROUND_RIGHT_BRACKET)
            Error("Missing expression.");
        SyntaxNode *expr = ParseExpression(0);
        if (*lexer.Get() != ROUND_RIGHT_BRACKET)
            Error("Missing close bracket. [ParseFactor]");
        return expr;
    }    
    if (t_token == KEYWORD || t_token == IDENTIFIER || t_token == NUMBER_INT ||
        t_token == NUMBER_FLOAT || t_token == STRING || t_token == CHAR)
    {
        // ј что делать со стрингами и зарезервированным словом? 
        if (t_token == CHAR)
        {
            s = new SymVar(token, new SymTypeChar(new BaseToken("char", lexer.GetLine(), lexer.GetPos(), CHAR)));
        }
        if (t_token == NUMBER_FLOAT)
        {
            s = new SymVar(token, new SymTypeDouble(new BaseToken("double", lexer.GetLine(), lexer.GetPos(), FLOAT)));
        }
        if (t_token == NUMBER_INT)
        {
            s = new SymVar(token, new SymTypeInteger(new BaseToken("int", lexer.GetLine(), lexer.GetPos(), INT)));
        }
        if (t_token == IDENTIFIER)
        {
            s = stack->Find(token->GetText());
            if (!s) Error("Undeclared variable or undeclared function.");
        }
        dynamic_cast <NodeVar*> (res)->symbol = s;
        return res;
    }
    return NULL;
};

void Parser::ParseFuncCall(SyntaxNode* &node, BaseToken* &oper)
{
    if (!dynamic_cast <SymFunc*> (dynamic_cast <NodeVar*> (node)->symbol))
        Error("Using a variable as a function call.");
    SymFunc *s = dynamic_cast <SymFunc*> (dynamic_cast <NodeVar*> (node)->symbol);
    node = new NodeCall(node, oper);
    dynamic_cast <NodeCall*> (node)->symbol = s;
    int i = 0;
    cout << "amount of params: " << s->args->symbols.size() << endl;
    int j = s->args->symbols.size() - 1;
    while (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        if (i>j) Error("Invalid amount of arguments.");
        SyntaxNode *expr = ParseExpression(priority_table[COMMA]+1);
        SymType* t_arg = expr->GetType();
        SymType* t_param = s->args->symbols[j-i]->GetType();
        if (!t_param)
        cout <<"xyi"<< endl;
        if (*t_param != t_arg)
            throw Exception(0, 0, "The type of argument does not match the type of parameter.");
        dynamic_cast <NodeCall*> (node)->AddArg(expr);
        if (*lexer.Peek() == EOF_)
            Error("Missing close round right bracket after function argument list.");
        if (*lexer.Peek() == COMMA)
            lexer.Get();
        ++i;

    }

    lexer.Get();
}

SymType* Parser::ParseType()
{
    SymType* type = NULL;
    BaseToken* token = lexer.Peek();
    switch (token->GetType())
    {
        case CHAR: 
            type = new SymTypeChar(token);
            lexer.Get();
            break;
        case INT:
            type = new SymTypeInteger(token);
            lexer.Get();
            break;
        case FLOAT:
            type = new SymTypeDouble(token);
            lexer.Get();
            break;
        case STRUCT:
            type = ParseTypeStruct();
            break;
        default:
            SymType* t = dynamic_cast <SymType*> (stack->Find(token->GetText()));
            if (!t)
                Error("Invalid type.");
            if (*t->name == STRUCT)
                Error("Missing 'struct'."); //тип структуры пишем только с зарезервированным словом struct
            type = new SymType(token);
            lexer.Get();
            break;
    }
    return type;
}

void Parser::ParseTypeArray()
{
    while (*lexer.Peek() == SQUARE_LEFT_BRACKET)
    {
        lexer.Get();
        BaseToken* size = lexer.Peek();
        if (*size == SQUARE_RIGHT_BRACKET)
            Error("Size of array is undefined.");
        if (*size != NUMBER_INT) 
            Error("Size of array has non-integer type.");
        dcl.push_back(size);
        lexer.Get();
        if (*lexer.Peek() != SQUARE_RIGHT_BRACKET)
            Error("Expected bracket close after array bounds.");
        lexer.Get();
    }
}

SymType* Parser::ParseTypeStruct()
{
    BaseToken* name = NULL;
    lexer.Get();
    if (*lexer.Peek() == IDENTIFIER)
    {
        name = new BaseToken(lexer.Peek()->GetText(), lexer.GetPos(), lexer.GetPos(), STRUCT);
        lexer.Get();
    }
    else
        name = new BaseToken(GetRandomName(), lexer.GetPos(), lexer.GetPos(), STRUCT);
    SymTypeRecord* old = dynamic_cast <SymTypeRecord*> (stack->Find(name->GetText()));
    if (old)
        if (*lexer.Peek() != FIGURE_LEFT_BRACKET) {return old;}
        else Error("'" + name->GetText() + "'" + " already declared.");
    else
        if (*lexer.Peek() != FIGURE_LEFT_BRACKET) 
            Error("'" + name->GetText() + "'" + " unknown type.");
    SymTypeRecord* type = new SymTypeRecord(name, new SymTable());
    stack->Add(type);
    StmtBlock *block = ParseBlock();
    type->fields = block->locals;
    if (!block->statements.empty()) //в объвлении структуры нельз€ инициализировать пол€
        Error("Noooooooooo!");
    //if (*lexer.Peek() == SEMICOLON) stack->Pop();
    return type;
}

Symbol* Parser::Translator(int end) // end - на каком месте закончили разбирать массив токинов
{
    SymType* type = new SymType(dcl[end--]);
    Symbol* symbol = type, *struct_type = NULL;
    int i, n;
    for (i=end; i>-1 && *dcl[i] != COMMA && *dcl[i] != ROUND_LEFT_BRACKET; i--)
    {
        BaseToken* curr = dcl[i];
        BaseToken* name = NULL;
        switch (curr->GetType())
        {
            case ROUND_RIGHT_BRACKET:
            {
                SymTable *func_sym_table = new SymTable;
                --i;//пропускаем ')'
                while (*dcl[i] != ROUND_LEFT_BRACKET)
                {
                    func_sym_table->Add(Translator(i));
                    i = begin;
                    if (*dcl[i] == COMMA) --i;
                }
                if (*dcl[i-1] == IDENTIFIER) name = dcl[--i];
                else name = new BaseToken(GetRandomName(), lexer.GetPos(), lexer.GetPos(), IDENTIFIER);
                symbol = new SymFunc(name, type, func_sym_table);
                break;
            }
            case SQUARE_LEFT_BRACKET:
                type = new SymTypeArray(dynamic_cast <SymType*> (symbol));
                while (*dcl[--i] == NUMBER_INT)
                    dynamic_cast <SymTypeArray*> (type)->AddLevel(GetValue <int> (dcl[i]));
                symbol = type;
                i++;
                break;
            case IDENTIFIER:
                n = stack->tables.size();
                struct_type = stack->tables[n-1]->Find(dcl[i]->GetText());
                if (struct_type) 
                    Error("'" + dcl[i]->GetText() + "' already declared.");
                symbol = new SymVar(dcl[i], type);
                break;
            case MULTIPLICATION:
                type = new SymTypePointer(symbol); 
                symbol = type;
                break;
            case STRUCT:
                struct_type = stack->Find(symbol->name->GetText());
                type = new SymTypeRecord(struct_type);
                symbol = type;
                break;
            default:
                Error("Hugger-mugger. [Translator]");
        }
    }
    begin = i;
    return symbol;
}

void Parser::ParseDeclarator()
{
    vector <BaseToken*> pointers;
    int i;
    for (i = 0; *lexer.Peek() == MULTIPLICATION; lexer.Get())
    {
        i++;
        pointers.push_back(lexer.Peek());
    }
    ParseDirectDeclarator();
    while (i-- > 0)
        dcl.push_back(pointers[i]);
}

void Parser::ParseDirectDeclarator()
{
    if (*lexer.Peek() == ROUND_LEFT_BRACKET)
    {
        lexer.Get();
        ParseDeclarator();
        if (*lexer.Peek() != ROUND_RIGHT_BRACKET)
            Error("Missing close bracket. [ParseDirectDeclarator]");
        lexer.Get();
    }
    else if (*lexer.Peek() == IDENTIFIER)
    {
        dcl.push_back(lexer.Peek());
        lexer.Get();
    }
    else if (*lexer.Peek() == ROUND_RIGHT_BRACKET || *lexer.Peek() == COMMA)//абстрактное объ€вление параметра функции
    {
        dcl.push_back(new BaseToken(GetRandomName(), lexer.GetPos(), lexer.GetPos(), IDENTIFIER)); 
        return;
    }
    if (*lexer.Peek() == ROUND_LEFT_BRACKET)//разбор параметров функции
    {
        dcl.push_back(lexer.Peek());
        lexer.Get();
        while (*lexer.Peek() != ROUND_RIGHT_BRACKET && *lexer.Peek() != EOF_)
        {
            SymType* t = ParseType();
            ParseDeclarator();
            dcl.push_back(t->name);
            if (*lexer.Peek() != COMMA && *lexer.Peek() != ROUND_RIGHT_BRACKET)
                Error("Invalid parameter list function.");
            if (*lexer.Peek() == COMMA) {dcl.push_back(lexer.Peek());lexer.Get();}
        }
        if (*lexer.Peek() != ROUND_RIGHT_BRACKET || *lexer.Peek() == EOF_)
            Error("Missing close round bracket.");
        dcl.push_back(lexer.Peek()); 
        lexer.Get();
    }
    else if (*lexer.Peek() == SQUARE_LEFT_BRACKET)
    {
        BaseToken* t = lexer.Peek();
        ParseTypeArray();
        dcl.push_back(t);
    }
    else if (*lexer.Peek() == SEMICOLON || *lexer.Peek() == COMMA ||
             *lexer.Peek() == ROUND_RIGHT_BRACKET ||//если парсили аргументы функции
             *lexer.Peek() == ASSIGN)//если объ€вление + инициализаци€ (реализуем только скал€р)
        return;
    else 
        Error("Invalid declaration. [ParseDirectDeclarator]");//например, зарезервированные слова под типы нельз€ использовать в качестве идентификатора
}

Statement* Parser::GetStmtAssignment()
{
    BaseToken* oper = lexer.Peek();
    lexer.Get();
    SyntaxNode *left = new NodeVar(dcl[0]);
    SyntaxNode *right = ParseExpression(priority_table[COMMA]+1);
    if (right == NULL) 
        Error("Missing operand.");
    if (*lexer.Peek() != SEMICOLON && *lexer.Peek() != COMMA) 
        Error("Invalid expression. [ParseDeclaration]");
    return new StmtAssignment(left, right);
}

Statement* Parser::ParseDeclaration()
{
    Symbol* s = NULL;
    curr_type = ParseType();
    ParseDeclarator();
    if (*curr_type->type == STRUCT) 
        dcl.push_back(new BaseToken("struct", 0, 0, STRUCT));
    dcl.push_back(curr_type->name);
    begin = dcl.size() - 1;
    s = Translator(begin);
    if (!dynamic_cast <SymTypeRecord*>(s))//ибо незачем эддить лишний раз структуру, если встретилось объ€вление типа 'struct {};'
        stack->Add(s);
    if (*lexer.Peek() == ASSIGN)
    {
        Statement* node = GetStmtAssignment();
        if (*lexer.Peek() != SEMICOLON && *lexer.Peek() != COMMA)
            Error("[ParseDeclaration assign]");
        return node;
    }
    else if (*lexer.Peek() == FIGURE_LEFT_BRACKET)
    {
        dcl.clear();
        SymFunc* f = dynamic_cast <SymFunc*> (stack->Top());
        if (!f)
            Error("It's not a function declaration.");
        f->body = ParseBlock();
        return NULL;
    }
    return NULL;
}

StmtBlock *Parser::ParseBlock()
{
    StmtBlock *block = new StmtBlock();
    stack->Push(block->locals);
    lexer.Get();
    while (*lexer.Peek() != FIGURE_RIGHT_BRACKET)
        Parse(block->statements);
    lexer.Get();
    stack->Pop();
    return block;
}

Statement* Parser::ParseStatement()
{
    Statement* result = NULL, *body = NULL, *if_body = NULL, *else_body = NULL;
    SyntaxNode *condition = NULL, *expr1 = NULL, *expr2 = NULL, *expr3 = NULL;
    BaseToken* token = NULL;
    TokenType curr_st = DEFAULT;
    switch (lexer.Peek()->GetType())
    {
        case FIGURE_LEFT_BRACKET:
            result = ParseBlock();
            break;

        case WHILE:
            curr_st = curr_stmt;
            curr_stmt = WHILE;
            lexer.Get();
            if (*lexer.Peek() != ROUND_LEFT_BRACKET)
                Error("Requires an expression in round brackets. [Where is '(' ?]");
            lexer.Get();
            condition = ParseExpression(0);
            if (!condition) 
                Error("Requires an expression. [Where is condition?]");
            if (*lexer.Peek() != ROUND_RIGHT_BRACKET) Error("Invalid condition. [While]");
            lexer.Get();
            body = ParseStatement();
            result = new StmtWhile(condition, body);
            curr_stmt = curr_st;
            break;

        case FOR:
            curr_st = curr_stmt;
            curr_stmt = FOR;
            lexer.Get();
            if (*lexer.Peek() != ROUND_LEFT_BRACKET) 
                Error("Requires an expression in round brackets.");
            lexer.Get();
            token = lexer.Peek();
            if (*token == INT || *token == FLOAT || *token == CHAR || *token == STRUCT)
                Error("Do not need to declare variables here.");
            expr1 = ParseExpression(0);
            if (*lexer.Peek() != SEMICOLON) Error("Invalid condition in the statement 'for'.[;]");
            lexer.Get();
            if (*lexer.Peek() == ROUND_RIGHT_BRACKET) Error("Invalid condition in the statement 'for'.");
            expr2 = ParseExpression(0);
            if (*lexer.Peek() != SEMICOLON) Error("Invalid condition in the statement 'for'.[;]");
            lexer.Get();
            expr3 = ParseExpression(0);
            if (*lexer.Peek() != ROUND_RIGHT_BRACKET) Error("Invalid condition in the statement 'for'.");
            lexer.Get();
            body = ParseStatement();
            result = new StmtFor(expr1, expr2, expr3, body);
            curr_stmt = curr_st;
            break;

        case IF:
            lexer.Get();
            if (*lexer.Peek() != ROUND_LEFT_BRACKET)
                Error("Requires a condition in the .");
            lexer.Get();
            condition = ParseExpression(0);
            if (!condition) 
                Error("Requires an expression.");
            lexer.Get();
            if_body = ParseStatement();
            if (*lexer.Peek() == SEMICOLON) lexer.Get();
            else_body = NULL;
            if (*lexer.Peek() == ELSE)
            {
                lexer.Get();
                else_body = ParseStatement();
            }
            result = new StmtIf(condition, if_body, else_body);
            break;

        case RETURN:
            //нет проверки откуда вызываетс€
            lexer.Get();
            result = new StmtReturn(ParseExpression(0));
            break;

        case CONTINUE:
            if (curr_stmt == DEFAULT) Error("'continue' used only in cycles.");
            lexer.Get();
            if (*lexer.Peek() != SEMICOLON) Error("Where is ';' ?"); 
            result = new StmtContinue();
            break;

        case BREAK:
            if (curr_stmt == DEFAULT) Error("'break' used only in cycles.");
            lexer.Get();
            if (*lexer.Peek() != SEMICOLON) Error("Where is ';' ?");
            result = new StmtBreak();
            break;

        default:
            //то, с чего не может начинатьс€ выражение... тут бы еще добавить нужно ~, *
            if (*lexer.Peek() != IDENTIFIER && *lexer.Peek() != NUMBER_FLOAT && *lexer.Peek() != NUMBER_INT &&
                *lexer.Peek() != ROUND_LEFT_BRACKET &&
                *lexer.Peek() != ADDITION && *lexer.Peek() != SUBSTRACTION &&
                //*lexer.Peek() != DECREASE && *lexer.Peek() != INCREASE &&
                *lexer.Peek() != SEMICOLON &&
                *lexer.Peek() != CHAR &&
                *lexer.Peek() != BIT_NOT)//если пустой оператор ;
                Error("No-NO-No." + lexer.Peek()->GetText());
            SyntaxNode *expr = ParseExpression(0);
            if (!expr->GetType()) Error("Invalid type. [GetType()]");
            result = new StmtExpr(expr);
            lexer.Get();
            break;
    }
    return result;
}

void Parser::Parse(vector <Statement*> &v)
{
    BaseToken* token = lexer.Peek();
    Statement* result = NULL;
    if (dynamic_cast <SymType*> (stack->Find(token->GetText())) || *token == STRUCT)
    {
        result = ParseDeclaration();
        dcl.clear();
    }
    else 
    {
        result = ParseStatement();
    }
    if (result) v.push_back(result);
    while (*lexer.Peek() == COMMA)
    {
        lexer.Get();
        dcl.clear();
        ParseDeclarator();
        dcl.push_back(curr_type->name);
        begin = dcl.size() - 1;
        stack->Add(Translator(begin));
        if (*lexer.Peek() == ASSIGN)
            v.push_back(GetStmtAssignment());
        if (*lexer.Peek() != SEMICOLON && *lexer.Peek() != COMMA) Error("Inal, stupid");
    }
    dcl.clear();
    if (*lexer.Peek() == SEMICOLON) //если разбирали просто выражение, заканчивающеес€ на ;
        lexer.Get();
}

string Parser::GetRandomName()
{
    stringstream name;
    name << "abstr_dcl_" << rand();
    return name.str();
}

void Parser::PrintTree(SyntaxNode *node, int width, int indent, ostream &out)
{
    node->Print(width, indent, out);
}

void Parser::PrintSymbols(ostream &out)
{
    if (!stack->tables[0]->symbols.empty()) 
    {
        out << "Global symbols:" << endl;
        stack->tables[0]->Print(out);
    }
    if (!stmt.empty())
    {
        out << "Global statements:" << endl;
        for (unsigned int i = 0; i < stmt.size(); ++i)
            stmt[i]->StmtPrint(out);
    }
}

Lexer::Lexer(const char* fin): scanner(fin), prep(NULL), last(NULL) {}
Lexer::~Lexer() 
{
    delete prep;
    delete last;
    prep = NULL;
    last = NULL;
}

BaseToken* Lexer::Get()
{
    last = prep ? prep : scanner.Next();
    prep = 0;
    return last;
}

void Lexer::UnGet()
{
    if (!last) return;
    prep = last;
    last = 0;
}

BaseToken* Lexer::Peek()
{
    BaseToken* token = Get();
    UnGet();
    return token;
}

int Lexer::GetPos()
{
    return scanner.curr_pos;
}

int Lexer::GetLine()
{
    return scanner.curr_line;
}

Parser::Parser(const char *fin): lexer(fin), curr_type(NULL), curr_stmt(DEFAULT), dcl(NULL), begin(0)
{
    Init(); 
    srand(time(NULL));
    stack = new SymTableStack();
    stack->Push(new SymTable());
    stack->Add(new  SymTypeInteger(new BaseToken("int", 0, 0, INT)));
    stack->Add(new  SymTypeDouble(new BaseToken("double", 0, 0, FLOAT)));
    stack->Add(new  SymTypeChar(new BaseToken("char", 0, 0, CHAR)));
}
Parser::~Parser() {}

void Parser::Error(const char *msg)
{
    throw Exception(lexer.GetLine(), lexer.GetPos(), msg);
}

void Parser::Error(const string msg)
{
    throw Exception(lexer.GetLine(), lexer.GetPos(), msg);
}

void Parser::Init()
{
    //POSTFIX
    priority_table[ROUND_LEFT_BRACKET] = 16;
    priority_table[ROUND_RIGHT_BRACKET] = 1000;
    priority_table[SQUARE_LEFT_BRACKET] = 16;
    priority_table[SQUARE_RIGHT_BRACKET] = 1000;
    priority_table[ARROW] = 16;
    priority_table[POINT] = 16;
    //priority_table[INCREASE] = 16;
    //priority_table[DECREASE] = 16;

    //PREFIX
    //increace/decreace = 15

    //BINARY
    priority_table[MULTIPLICATION] = 13;
    priority_table[DIVISION] = 13;
    priority_table[MODULO] = 13;
    priority_table[SUBSTRACTION] = 12;
    priority_table[ADDITION] = 12;
    priority_table[BIT_SHIFT_LEFT] = 11;
    priority_table[BIT_SHIFT_RIGHT] = 11;
    priority_table[GREATER] = 10;
    priority_table[LESS] = 10;
    priority_table[GREATER_EQUAL] = 10;
    priority_table[LESS_EQUAL] = 10;
    priority_table[EQUAL] = 9;
    priority_table[NOT_EQUAL] = 9;
    priority_table[BIT_AND] = 8;
    priority_table[BIT_XOR] = 7;
    priority_table[BIT_OR] = 6;
    priority_table[AND] = 5;
    priority_table[OR] = 4;
    //ternary ?: = 3
    priority_table[ASSIGN] = 2;
    priority_table[ADD_ASSIGN] = 2;
    priority_table[SUB_ASSIGN] = 2;
    priority_table[MUL_ASSIGN] = 2;
    priority_table[DIV_ASSIGN] = 2;
    priority_table[MOD_ASSIGN] = 2;
    priority_table[BIT_SHIFT_LEFT_ASSIGN] = 2;
    priority_table[BIT_SHIFT_RIGHT_ASSIGN] = 2;
    priority_table[BIT_AND_ASSIGN] = 2;
    priority_table[BIT_XOR_ASSIGN] = 2;
    priority_table[BIT_OR_ASSIGN] = 2;
    priority_table[COMMA] = 1;
    
    priority_table[SEMICOLON] = 1000;
    priority_table[EOF_] = 1000;


    //UNARY
    //sizeof = 15
    unary_oper[NOT] = true;
    unary_oper[BIT_NOT] = true;            //~
    unary_oper[BIT_AND] = true;            //get address 
    //unary_oper[INCREASE] = true;
    //unary_oper[DECREASE] = true;
    unary_oper[ADDITION] = true;
    unary_oper[SUBSTRACTION] = true;
    unary_oper[MULTIPLICATION] = true;    //dereference

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
    right_assoc_oper[BIT_NOT] = true;
    right_assoc_oper[NOT] = true;
    right_assoc_oper[BIT_AND] = true;
}