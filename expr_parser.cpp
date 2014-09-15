#include "exception.h"
#include "_parser.h"

#define POSTFIX 14
#define UNARY 13
#define MAX 15

const int INF = numeric_limits<int>::max();

Parser::Parser(const char* fin): lexer(fin), inLoop(false), parseFunc(false)
{
    Init();
}

Parser::~Parser() {}

void Parser::Parse()
{
    BaseToken* token = lexer.Peek();

    if (*token == STRUCT
        || dynamic_cast<SymType*>(symStack.Find(token->GetText())))
    {
        ParseDeclaration();
    }
    else
    {
        Statement* stmt = ParseStatement();
        stmtStack.push_back(stmt);
    }
    if (*lexer.Peek() == SEMICOLON)
    {
        lexer.Get();
    }
}

SyntaxNode* Parser::ParseExpression(int precedence)
{
    if (precedence == UNARY)
    {
        BaseToken* oper = GetUnary();
        if (oper)
        {
            SyntaxNode* expr = ParseExpression(precedence);
            SyntaxNode* node = new NodeUnaryOp(oper, expr);

            // type check
            node->GetType();
            return node;
        }
    }

    if (precedence == MAX)
    {
        return ParsePrimaryExpression();
    }

    SyntaxNode* left = ParseExpression(precedence+1);
    if (!left)
    {
        return NULL;
    }

    BaseToken* oper = lexer.Peek();
    TokenType type = oper->GetType();
    TokenType subType = oper->GetSubType();
    while (type == OPERATOR && precedences[subType] == precedence)
    {
        lexer.Get();
        if (precedence == POSTFIX)
        {
            if (subType == SQUARE_LEFT_BRACKET)
            {
                ParseArrIndex(left);
            }

            if (subType == ROUND_LEFT_BRACKET)
            {
                ParseFuncCall(left);
            }

            if (subType == POINT || subType == ARROW)
            {
                ParseMemberSelection(left, oper);
            }
        }
        else
        {
            SyntaxNode* right = ParseExpression(precedence + (right_assoc_oper[subType] == true ? 0 : 1));
            left = new NodeBinaryOp(left, oper, right);
        }

        // type check
        left->GetType();

        oper = lexer.Peek();
        type = oper->GetType();
        subType = oper->GetSubType();
    }

    return left;
};

SyntaxNode* Parser::ParsePrimaryExpression()
{
    if (*lexer.Peek() == SEMICOLON
        || *lexer.Peek() == KEYWORD)
    {
        return NULL;
    }

    SyntaxNode* result = NULL;
    BaseToken* token = lexer.Get();

    if (*token == IDENTIFIER || *token == CONSTANT || *token == STRING)
    {
        Symbol* symbol = symStack.Find(token->GetText());
        if (*token == IDENTIFIER)
        {
            if (!symbol)
            {
                Error("identifier is undefined");
            }
            result = new NodeVar(symbol);
        }
        else if (*token == NUMBER_INT)
        {
            result = new NodeVar(new SymVar(token, intType));
        }
        else if (*token == NUMBER_FLOAT)
        {
            result = new NodeVar(new SymVar(token, floatType));
        }
        else if (*token == CHARACTER)
        {
            result = new NodeVar(new SymVar(token, charType));
        }
        else if (*token == STRING)
        {
            result = new NodeVar(new SymVar(token, stringType));
        }
    }
    else if (*token == OPERATOR && *token == ROUND_LEFT_BRACKET)
    {
        result = ParseExpression();
        Expected(lexer.Get()->GetSubType(), ROUND_RIGHT_BRACKET);
    }
    else
    {
        Error("expected an expression");
    }
    return result;
}

void Parser::ParseFuncCall(SyntaxNode*& node)
{
    SymTypeFunc* type = dynamic_cast<SymTypeFunc*>(node->GetType());
    if (!type)
    {
        Error("expression must have (pointer-to-) function type");
    }
    node = new NodeCall(type, node);
    while (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        SyntaxNode* arg = ParseExpression(precedences[COMMA]+1);

        if (*lexer.Peek() == EOF_)
        {
            Error("expected a `)`");
        }

        if (*lexer.Peek() == COMMA)
        {
            lexer.Get();
        }

        dynamic_cast<NodeCall*>(node)->AddArg(arg);
    }

    lexer.Get();
}

void Parser::ParseArrIndex(SyntaxNode*& node)
{
    if (*lexer.Peek() == SQUARE_RIGHT_BRACKET)
    {
        Error("unknown size");
    }

    SyntaxNode* index = ParseExpression();
    node = new NodeArr(node, index);

    Expected(lexer.Get()->GetSubType(), SQUARE_RIGHT_BRACKET);
}

void Parser::ParseMemberSelection(SyntaxNode*& node, BaseToken* oper)
{
    Expected(lexer.Peek()->GetSubType(), IDENTIFIER);

    SymTypeStruct* st = NULL;
    SymType* type = node->GetType();
    if (dynamic_cast<SymTypePointer*>(type))
    {
        st = dynamic_cast<SymTypeStruct*>(dynamic_cast<SymTypePointer*>(type)->refType);
        if (!st)
        {
            Error("expression must have pointer-to-struct type");
        }
    }
    else
    {
        st = dynamic_cast<SymTypeStruct*>(type);
        if (!st)
        {
            Error("expression must have struct type");
        }
    }

    SyntaxNode* field = ParseExpression();
    if (!st->fields->Find(field->token->GetText()))
    {
        Error("struct has no this member");
    }
    node = new NodeBinaryOp(node, oper, field);
}

void Parser::PrintStmtTrees(int width, int indent, ostream& out)
{
    for (int i = 0, size = stmtStack.size(); i < size; ++i)
    {
        out << "stmt " << i << ":" << endl;
        stmtStack[i]->StmtPrint(out, indent);
        out << endl;
    }
}

void Parser::PrintNodeTrees(int width, int indent, ostream& out)
{
    for (int i = 0, size = nodeStack.size(); i < size; ++i)
    {
        out << "tree " << i << ":" << endl;
        nodeStack[i]->Print(width, indent, out);
        out << endl;
    }
}

void Parser::PrintTree(SyntaxNode* node, int width, int indent, ostream& out)
{
    node->Print(width, indent, out);
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

BaseToken* Parser::GetUnary()
{
    BaseToken* oper = lexer.Peek();
    if (oper && *oper == OPERATOR && unary_oper[oper->GetSubType()])
    {
        return lexer.Get();
    }
    return NULL;
}

bool Parser::Eof()
{
    return *lexer.Peek() == EOF_ ? true : false;
}

void Parser::PrintSymTables(ostream& out)
{
    for (int i = 0, size = symStack.tables.size(); i < size; ++i)
    {
        if (symStack.tables[i]->GetSize() > 0)
        {
            out << "table " << i << ":" << endl;
        }
        else
        {
            continue;
        }
        symStack.tables[i]->Print(out);
        out << endl;
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
    //right_assoc_oper[ADDITION] = true;// unary
    //right_assoc_oper[SUBSTRACTION] = true;// unary
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