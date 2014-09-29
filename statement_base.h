#pragma once

//-----------------------------------------------------------------------------
class Statement
{
public:
    Statement();
    ~Statement();

    virtual void Generate(AsmCode&);
    virtual void StmtPrint(ostream&, int);
};
