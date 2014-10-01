#include <iostream>
#include <fstream>
#include <string>

#include "exception.h"
#include "simple_parser.h"
#include "_parser.h"

using namespace std;

void openFile(char* name1, char* name2)
{
    ifstream fin(name1);
    ofstream fout(name2);
    if (!fin)
    {
        cerr << "Error: Can't open file \"" << name1 << "\".\n";
        exit(-1);
    }
    if (!fout)
    {
        cerr << "Error: Can't open file \"" << name2 << "\".\n";
        exit(-1);
    }
    cout << "Files are successfully opened." << endl;
}

int main(int argc, char* argv[])
{
    cout << "C language subset compiler" << endl
         << "Author: Yaroslava Gura, B8303A, FEFU" << endl;

    if (argc <= 1)
    {
        cout << "Usage: " << argv[0] << " <key: -s -sp -p -d -o> <input file name> <output file name>" << endl;
        return EXIT_SUCCESS;
    }

    openFile(argv[2], argv[3]);
    ofstream fout(argv[3]);
    //ofstream fout("out.out");

    try
    {
        //lexical analysis
        if (!strcmp(argv[1], "-s"))
        {
            //char p[100];
            //cin.getline(p, 100);
            //Scanner scanner(p);

            Scanner scanner(argv[2]);
            for (BaseToken* token = scanner.Next();
                 token->GetType() != EOF_;
                 token = scanner.Next())
            {
                token->Print(fout);
            }
        }
        //analysis of the simplest expressions
        else if (!strcmp(argv[1], "-sp"))
        {
            SimpleParser parser(argv[2]);

            //char p[100];
            //cin.getline(p, 100);
            //SimpleParser parser(p);

            int index = 1;
            while (!parser.Eof())
            {
                fout << "tree " << index++ << ":" << endl;
                Node* root = parser.ParseExpr();
                parser.PrintTree(root, 5, 0, fout);
                fout << endl;
            }
        }
        //parsing of expressions
        else if (!strcmp(argv[1], "-p"))
        {
            Parser parser(argv[2], "");

            //char p[100];
            //cin.getline(p, 100);
            //Parser parser(p, "");

            int index = 1;

            while (!parser.Eof())
            {
                fout << "tree " << index++ << ":" << endl;
                SyntaxNode* root = parser.ParseExpression();
                parser.PrintTree(root, 10, 0, fout);
                fout << endl;
                parser.Next();
            }
        }
        //parsing of declarations
        else if (!strcmp(argv[1], "-d"))
        {
            //char p[100];
            //cin.getline(p, 100);
            //Parser parser(p, "");

            Parser parser(argv[2], "");

            while (!parser.Eof())
            {
                parser.Parse();
            }

            //see tasks.todo
            //parser.PrintSymTables(fout);
            //parser.PrintNodeTrees(5, 5, fout);
            //parser.PrintStmtTrees(5, 5, fout);
        }
        //parsing of declarations
        else if (!strcmp(argv[1], "-g"))
        {
            //char fin_[100];
            //cin.getline(fin_, 100);

            string asmout =  string((char*) argv[2]) + ".asm";
            //string asmout = "out.asm";

            Parser parser(argv[2], asmout.c_str());
            //Parser parser(fin_, asmout.c_str());

            while (!parser.Eof())
            {
                parser.Parse();
            }

            parser.GenerateCode();
        }
    }
    catch (Exception exp)
    {
        fout << exp.GetException() << endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        cerr << "ERROR: unknown exception.";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}