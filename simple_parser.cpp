#include <ostream>
#include <iomanip>
#include "simple_parser.h"
#include "exception.h"
#include "scanner.h"

SimpleParser::SimpleParser(const char* fin): scanner(fin) {}

SimpleParser::~SimpleParser()
{
    //scanner.~Scanner();
}

Node* SimpleParser::ParseExpr()
{
    Node* left = ParseTerm();
    if (left == NULL) return NULL;
    BaseToken* token = scanner.Get();
    TokenType t_token = token->GetType();
    //if (t_token == ADDITION)
    //    return new Node(left, ParseExpr(), token);
    //if (t_token == SUBSTRACTION)
    //{
    //    Token *add = new Token("+", 0, 0, ADDITION);
    //    TokenNumberInt *nul = new TokenNumberInt("0", 0, 0, NUMBER_INT, 0);
    //    Node* subtrahend = new Node(new Node(NULL, NULL, nul), ParseFactor(), token);
    //    if ((token = scanner.Next())->GetType() != LX_EOF && token->GetType() != ROUND_RIGHT_BRACKET)
    //        return new Node(left, new Node(subtrahend, ParseExpr(), token), add);
    //    return new Node(left, new Node(subtrahend, new Node(NULL, NULL, nul), add), add);
    //}
    while (/*token->TypeIs(SUBSTRACTION, ADDITION)*/t_token == SUBSTRACTION
           || t_token == ADDITION)
    {
        Node* right = ParseTerm();
        if (right == NULL)
            throw Exception(scanner.curr_line, scanner.curr_pos, "Missing operand.");
        left = new Node(left, right, token);
        token = scanner.Get();
        t_token = token->GetType();
    }
    return left;
};

Node* SimpleParser::ParseTerm()
{
    Node* left = ParseFactor();
    if (left == NULL) return NULL;
    BaseToken* token = scanner.Next();
    TokenType t_token = token->GetType();
    if (t_token == MULTIPLICATION || t_token == DIVISION)
        return new Node(left, ParseTerm(), token); 
    return left;
};

Node* SimpleParser::ParseFactor()
{
    BaseToken* token = scanner.Next();
    TokenType t_token = token->GetType();
    if (!scanner.HasNext()) return NULL;
    if (token->GetType() == ROUND_LEFT_BRACKET)
    {
        Node* expr = ParseExpr();
        BaseToken* token = scanner.Get();
        if (token->GetType() == ROUND_RIGHT_BRACKET) return expr;
        throw Exception(scanner.curr_line, scanner.curr_pos, "Missing close braket.");
    }
    if (t_token == IDENTIFIER
        || t_token == NUMBER_INT
        || t_token == NUMBER_DOUBLE)
        return new Node(NULL, NULL, token);
    throw Exception(scanner.curr_line, scanner.curr_pos, "Missing operand.");
};

void SimpleParser::PrintTree(Node* node, int width, int indent, ostream& out)
{
    if (!node) return;
    PrintTree(node->left, width, indent+width, out);
    if (indent) out << setw(indent);
    out << node->token->GetText()
        << ((node->left && node->right) ? " <": "")
        << endl;
    PrintTree(node->right, width, indent+width, out);
}