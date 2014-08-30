#include "simple_parser.h"
#include "exception.h"
#include "scanner.h"

SimpleParser::SimpleParser(const char* fin): lexer(fin) {}

SimpleParser::~SimpleParser() {}

Node* SimpleParser::ParseExpr()
{
    Node* left = ParseTerm();

    if (left == NULL) return NULL;

    BaseToken* token = lexer.Peek();

    while (*token == SUBSTRACTION || *token == ADDITION)
    {
        lexer.Get();
        Node* right = ParseTerm();
        if (right == NULL || *right->token == EOF_)
        {
            throw Exception(lexer.GetLine(), lexer.GetPos(), "expected an expression");
        }

        left = new Node(left, right, token);
        token = lexer.Peek();
    }

    return left;
};

Node* SimpleParser::ParseTerm()
{
    Node* left = ParseFactor();

    if (left == NULL) return NULL;

    BaseToken* token = lexer.Peek();

    while (*token == MULTIPLICATION || *token == DIVISION)
    {
        lexer.Get();
        Node* right = ParseFactor();
        if (right == NULL || *right->token == EOF_)
        {
            throw Exception(lexer.GetLine(), lexer.GetPos(), "expected an expression");
        }

        left = new Node(left, right, token);
        token = lexer.Peek();
    }

    return left;
};

Node* SimpleParser::ParseFactor()
{
    BaseToken* token = lexer.Peek();

    if (*token == EOF_) return NULL;

    if (*token == ROUND_LEFT_BRACKET)
    {
        lexer.Get();
        Node* expr = ParseExpr();
        BaseToken* token = lexer.Peek();
        if (*token == ROUND_RIGHT_BRACKET)
        {
            lexer.Get();
            return expr;
        }

        throw Exception(lexer.GetLine(), lexer.GetPos(), "expected a `)`");
    }

    if (*token == IDENTIFIER || *token == CONSTANT || *token == STRING)
    {
        lexer.Get();
        return new Node(NULL, NULL, token);
    }

    throw Exception(lexer.GetLine(), lexer.GetPos(), "expected an expression");
};

void SimpleParser::PrintTree(Node* node, int width, int indent, ostream& out)
{
    if (!node) return;

    PrintTree(node->left, width, indent+width, out);

    if (indent) out << setw(indent);

    out << node->token->GetText()
        << (node->left && node->right ? " <" : "")
        << endl;

    PrintTree(node->right, width, indent+width, out);
}

bool SimpleParser::Eof()
{
    return *lexer.Peek() == EOF_ ? true : false;
}