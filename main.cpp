#include <iostream>
#include <fstream>
#include <string>
#include "exception.h"
#include "simple_parser.h"
#include "_parser.h"
using namespace std;

void openFile(char* name)
{
    ifstream inf(name);
    if (!inf)
    {
        cout << "Error: Can't open file '" << name << "'.\n";
        exit(-1);
    }
    cout << "File is successfully opened." << endl;
}

int main(int argc, char* argv[])
{
    ofstream fout("1.in");
    /*cout << "C Compiler [Version 0.1]" << endl << "Copyright (c) Gura Yaroslava, 2013 " << endl;
    if (argc <= 1)
    {
        cout << "Usage: " << argv[0] << " <key: -s -sp -p -d -o> <input file name> <output file name>" << endl;
        exit(1);
    }
    ofstream fout(argv[3]);
    openFile(argv[2]);*/
    try
    {
        /*if (!strcmp(argv[1], "-s"))
        {
            Scanner scanner(argv[2]);
            fout << "+-----------------------------------------------------------------------------------------+" << endl;
            fout << setw(20) << "Type" << "\t";
            fout << setw(10) << "Line" << "\t";
            fout << setw(10) << "Position" << "\t";
            fout << setw(10) << "Text" << "\t";
            fout << setw(10) << "Value" << "\t" << endl;
            fout << "+-----------------------------------------------------------------------------------------+" << endl;
            while (scanner.HasNext()) 
            {
                BaseToken *token = scanner.Next();
                if (token->GetType() != NEWLINE && token->GetType() != COMMENT)
                    token->Print(fout);
            }
        }
        else if (!strcmp(argv[1], "-sp"))
        {
            SimpleParser parser(argv[2]);
            Node *root = parser.ParseExpr();
            parser.PrintTree(root, 5, 0, fout);
        }
        else if (!strcmp(argv[1], "-p"))
        {
            Parser parser(argv[2]);
            SyntaxNode *root = parser.ParseExpression(0);
            parser.PrintTree(root, 10, 0, fout);
            /*BaseToken *t = new TokenVal <TokenType> ("h", 0,0,OPERATOR, OPERATOR);
            cout << GetValue <TokenType> (t) ;*/
        /*}
        else if (!strcmp(argv[1], "-d_s"))
        {*/
            char p[100];
            cin.getline(p, 100);
            Parser parser(p);
            //Parser parser(argv[2]);
            while (*parser.lexer.Peek() != LX_EOF)
                parser.Parse(parser.stmt);
            parser.PrintSymbols(cout);
            int a = 1;
            +a;
            -a;
        //}
    }
    catch (Exception exp)
    {
        cout << exp.GetException() << endl;
        exit(-1);
    }
}