#include "exception.h"
#include "_parser.h"

#define POSTFIX 14
#define UNARY 13
#define MAX 15

const int INF = numeric_limits<int>::max();

Parser::Parser(const char* fin): lexer(fin)
{
    Init();
}

Parser::~Parser() {}

void Parser::Parse(ostream& out)
{
    BaseToken* token = lexer.Peek();
    while (*token != EOF_)
    {
        if (*token == INT
            || *token == FLOAT
            || *token == CHAR
            || *token == STRUCT
            || dynamic_cast <SymType*> (stack.Find(token->GetText())))
        {
            ParseDeclaration();
        }
        else
        {
            SyntaxNode* tree = ParseExpression();
            PrintTree(tree, 5, 5, out);
        }
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
            return new NodeUnaryOp(oper, expr);
        }
    }

    if (precedence == MAX)
    {
        return ParsePrimaryExpression();
    }

    SyntaxNode* left = ParseExpression(precedence+1);
    if (!left)
    {
        cout << "LEFT IS NULL" << endl;
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
            //if (right == NULL)
            //{
            //    left = new NodeVar(left->token);
            //}
            //else
            //{
                left = new NodeBinaryOp(left, oper, right);
            //}
        }

        oper = lexer.Peek();
        type = oper->GetType();
        subType = oper->GetSubType();
    }

    return left;
};

SyntaxNode* Parser::ParsePrimaryExpression()
{
    SyntaxNode* result = NULL;
    BaseToken* token = lexer.Get();
    if (token->GetSubType() == SEMICOLON)
    {
        return NULL;
    }

    TokenType type = token->GetType();
    TokenType subType = token->GetSubType();
    if (type == IDENTIFIER || type == CONSTANT || type == STRING)
    {
        result = new NodeVar(token);
    }
    else if (type == OPERATOR && subType == ROUND_LEFT_BRACKET)
    {
        result = ParseExpression();
        if (lexer.Peek()->GetSubType() != ROUND_RIGHT_BRACKET)
        {
            Error("expected a `)`");
        }
        lexer.Get();
    }
    else if (type == KEYWORD)
    {
        Error("what are you doing here?");
    }
    else
    {
        Error("expected an expression");
    }
    return result;
}

void Parser::ParseFuncCall(SyntaxNode*& node)
{
    node = new NodeCall(node);
    while (lexer.Peek()->GetSubType() != ROUND_RIGHT_BRACKET)
    {
        SyntaxNode* arg = ParseExpression(precedences[COMMA]+1);

        if (lexer.Peek()->GetSubType() == EOF_)
        {
            Error("expected a `)`");
        }

        if (lexer.Peek()->GetSubType() == COMMA)
        {
            lexer.Get();
        }

        dynamic_cast <NodeCall*> (node)->AddArg(arg);
    }

    lexer.Get();
}

void Parser::ParseArrIndex(SyntaxNode*& node)
{
    if (lexer.Peek()->GetSubType() == SQUARE_RIGHT_BRACKET)
    {
        Error("incomplete type is not allowed");
    }

    SyntaxNode* index = ParseExpression();
    node = new NodeArr(node, index);

    if (lexer.Peek()->GetSubType() != SQUARE_RIGHT_BRACKET)
    {
        Error("expected a `]`");
    }

    lexer.Get();
}

void Parser::ParseMemberSelection(SyntaxNode*& node, BaseToken* oper)
{
    if (lexer.Peek()->GetSubType() != IDENTIFIER)
    {
        Error("expected a member name");
    }

    node = new NodeBinaryOp(node, oper, ParseExpression());
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

BaseToken* Parser::GetUnary()
{
    BaseToken* oper = lexer.Peek();
    if (oper && oper->GetType() == OPERATOR && unary_oper[oper->GetSubType()])
    {
        return lexer.Get();
    }
    return NULL;
}

bool Parser::Eof()
{
    return lexer.Peek()->GetType() == EOF_ ? true : false;
}

void Parser::Init()
{
    SymTypeScalar* intType = new SymTypeScalar(new BaseToken("", 0, 0, KEYWORD, INT));
    SymTypeScalar* floatType = new SymTypeScalar(new BaseToken("", 0, 0, KEYWORD, FLOAT));
    SymTypeScalar* charType = new SymTypeScalar(new BaseToken("", 0, 0, KEYWORD, CHAR));

    SymTable* predefined = new SymTable();
    predefined->Add(intType);
    predefined->Add(floatType);
    predefined->Add(charType);
    stack.Push(predefined);
    stack.Push(new SymTable());

    precedences[BOF_] = INF;
    precedences[EOF_] = INF;

    //precedences[IDENTIFIER] = 14;
    //precedences[CONSTANT] = 14;
    //precedences[STRING] = 14;

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