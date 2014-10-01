#include "exception.h"
#include "_parser.h"

#define POSTFIX 14
#define UNARY 13
#define MAX 15

const int INF = numeric_limits<int>::max();

Parser::Parser(const char* fin, const char* asmout):
    lexer(fin),
    generator(asmout),
    inLoop(false),
    parseFunc(NULL)
{
    counter = 0;
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
            SyntaxNode* node = new NodeUnaryOp(counter++, oper, expr);

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
            left = new NodeBinaryOp(counter++, left, oper, right);
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
    if (*lexer.Peek() == SEMICOLON)
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
            Expected(symbol != NULL, "identifier is undefined");
            result = new NodeVar(counter++, symbol);
        }
        else
        {
            switch(token->GetSubType())
            {
            case NUMBER_INT:
                result = new NodeVar(counter++, new SymVar(token, intType));
                break;
            case NUMBER_FLOAT:
                result = new NodeVar(counter++, new SymVar(token, floatType));
                break;
            case CHARACTER:
                result = new NodeVar(counter++, new SymVar(token, charType));
                break;
            case STRING:
                result = new NodeVar(counter++, new SymVar(token, stringType));
                break;
            }
            consts.push_back(result);
        }
    }
    else if (*token == OPERATOR && *token == ROUND_LEFT_BRACKET)
    {
        result = ParseExpression();
        Expected(lexer.Get()->GetSubType(), ROUND_RIGHT_BRACKET);
    }
    else if (*token == PRINTF)
    {
        result = ParsePrintf(token);
    }
    else if (*token == KEYWORD)
    {
        return NULL;
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
    Expected(type != NULL, "expression must have (pointer-to-) function type");

    node = new NodeCall(counter++, type, node);
    while (*lexer.Peek() != ROUND_RIGHT_BRACKET)
    {
        SyntaxNode* arg = ParseExpression(precedences[COMMA]+1);
        Expected(*lexer.Peek() != EOF_, "expected a `)`");

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
    Expected(*lexer.Peek() != SQUARE_RIGHT_BRACKET, "unknown size");

    SyntaxNode* index = ParseExpression();
    node = new NodeArr(counter++, node, index);

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
        Expected(st != NULL, "expression must have pointer-to-struct type");
    }
    else
    {
        st = dynamic_cast<SymTypeStruct*>(type);
        Expected(st != NULL, "expression must have struct type");
    }

    SyntaxNode* field = ParseExpression();
    Expected(st->fields->Find(field->token->GetText()) != NULL, "struct has no this member");
    node = new NodeBinaryOp(counter++, node, oper, field);
}

SyntaxNode* Parser::ParsePrintf(BaseToken* token)
{
    NodePrintf* result = NULL;
    Expected(*lexer.Get() == ROUND_LEFT_BRACKET, "expected a `(`");
    SyntaxNode* format = ParseExpression(precedences[COMMA] + 1);
    SymType* type = format->GetType();
    Expected(type == stringType, "expected parameter of char*");
    result = new NodePrintf(counter++, token, format);
    if (*lexer.Peek() == COMMA)
    {
        lexer.Get();
        while (true)
        {
            SyntaxNode* arg = ParseExpression(precedences[COMMA] + 1);
            Expected(arg != NULL, "expected argument");
            result->AddArg(arg);
            if (*lexer.Peek() == ROUND_RIGHT_BRACKET)
            {
                break;
            }
            Expected(*lexer.Get() == COMMA, "expected a `,`");
        }
    }
    Expected(*lexer.Get() == ROUND_RIGHT_BRACKET, "expected a `)`");
    return result;
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

void Parser::Expected(bool actual, const char* msg)
{
    bool expected = true;
    if (actual != expected)
    {
        Error(msg);
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

void Parser::Next()
{
    if (*lexer.Peek() == SEMICOLON)
    {
        lexer.Get();
    }
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


void Parser::GenerateCode()
{
    //generate consts
    for (int i = 0, size = consts.size(); i < size; ++i)
    {
        consts[i]->GenerateData(generator.data);
    }

    //generate globals symbols
    symStack.Top()->GenerateData(generator.data);

    //generate function declarations
    symStack.Top()->GenerateCode(generator.code);

    //start
    generator.code.AddCmd(new AsmLabel("start"));

    //call main function
    generator.code.AddCmd(cmdSUB, ESP, 4);//!!!
    generator.code.AddCmd(cmdCALL, new AsmArgLabel("main"));
    generator.code.AddCmd(cmdADD, ESP, 4);//!!!

    //end of start
    generator.code.AddCmd(cmdRET, new AsmArg());

    //generate body of main function
    generator.Generate();
}
