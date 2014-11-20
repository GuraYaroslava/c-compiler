#pragma once

//-----------------------------------------------------------------------------
class Statement
{
public:
    Statement();
    ~Statement();

    virtual Statement* Optimize(bool&, BaseParser&);
    virtual void Generate(AsmCode&);
    virtual void Print(int, ostream&s);
    virtual void SetUnUsed(BaseParser&);
};
