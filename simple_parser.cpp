#include <ostream>
#include <iomanip>

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
    TokenType subType = token->GetSubType();

    while (subType == SUBSTRACTION || subType == ADDITION)
    {
        lexer.Get();
        Node* right = ParseTerm();
        if (right == NULL || right->token->GetType() == EOF_)
        {
            throw Exception(lexer.GetLine(), lexer.GetPos(), "Expected an expression");
        }

        left = new Node(left, right, token);
        token = lexer.Peek();
        subType = token->GetSubType();
    }

    return left;
};

Node* SimpleParser::ParseTerm()
{
    Node* left = ParseFactor();

    if (left == NULL) return NULL;

    BaseToken* token = lexer.Peek();
    TokenType subType = token->GetSubType();

    while (subType == MULTIPLICATION || subType == DIVISION)
    {
        lexer.Get();
        Node* right = ParseFactor();
		if (right == NULL || right->token->GetType() == EOF_)
        {
            throw Exception(lexer.GetLine(), lexer.GetPos(), "Expected an expression");
        }

        left = new Node(left, right, token);
        token = lexer.Peek();
        subType = token->GetSubType();
        //return new Node(left, ParseFactor(), token);
    }

    return left;
};

Node* SimpleParser::ParseFactor()
{
    BaseToken* token = lexer.Peek();
    TokenType type = token->GetType();
    TokenType subType = token->GetSubType();

    if (type == EOF_) return NULL;

    if (subType == ROUND_LEFT_BRACKET)
    {
        lexer.Get();
        Node* expr = ParseExpr();
        BaseToken* token = lexer.Peek();
        if (token->GetSubType() == ROUND_RIGHT_BRACKET)
        {
            lexer.Get();
            return expr;
        }

        throw Exception(lexer.GetLine(), lexer.GetPos(), "Expected a `)`");
    }

    if (type == IDENTIFIER || type == CONSTANT || type == STRING)
    {
        lexer.Get();
        return new Node(NULL, NULL, token);
    }

    throw Exception(lexer.GetLine(), lexer.GetPos(), "Expected an expression");
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
    return lexer.Peek()->GetType() == EOF_ ? true : false;
}