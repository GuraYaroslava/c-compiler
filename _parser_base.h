#pragma once

#include <string>

class SymTable;

class BaseParser
{
public:
    virtual void SetUnUsed(const std::string&)
    {

    }

    virtual void PushLocals(SymTable*)
    {

    }

    virtual void PopLocals()
    {

    }
};
