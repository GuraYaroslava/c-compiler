#pragma once

#include <map>
#include <vector>
#include <string>

#include "token.h"
#include "statement.h"

using namespace std;

class SymType;

//-----------------------------------------------------------------------------
class Symbol
{
public:
    BaseToken* name;

    Symbol(BaseToken*);
    ~Symbol();

    virtual SymType* GetType();

    virtual void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymType: public Symbol
{
public:
    SymType(BaseToken*);
    ~SymType();

    virtual bool operator == (SymType*);
    virtual bool operator != (SymType*);
};

//-----------------------------------------------------------------------------
class SymTypeScalar: public SymType
{
public:
    SymTypeScalar(BaseToken*);
    ~SymTypeScalar();

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypeArray: public SymType
{
private:
    int size;
    SymType* type;

public:
    SymTypeArray(int, SymType*);
    ~SymTypeArray();

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypeStruct: public SymType
{
private:
    SymTable* fields;

public:
    SymTypeStruct(BaseToken*, SymTable*);
    ~SymTypeStruct();

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypePointer: public SymType
{
private:
    Symbol* refType;

public:
    SymTypePointer(SymType*);
    ~SymTypePointer();

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypeFunc: public SymType
{
private:
    SymType* type;
    SymTable* params;
    StmtBlock* body;

public:
    SymTypeFunc(SymType*, SymTable*, StmtBlock*);
    ~SymTypeFunc();

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymVar: public Symbol
{
protected:
    SymType* type;

public:
    SymVar(BaseToken*, SymType*);
    SymVar(BaseToken*);
    ~SymVar();

    SymType* GetType();
    void SetType(SymType*);

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTable
{
public:
    vector <Symbol*> symbols;

    map <string, int> GetIndexByName;

    SymTable();
    ~SymTable();

    Symbol* Find(const string&);

    void Add(Symbol*);

    void Print(ostream&);
};

//-----------------------------------------------------------------------------
class SymTableStack
{
public:
    vector <SymTable*> tables;

    SymTableStack();
    ~SymTableStack();

    Symbol* Find(const string&);

    void Add(Symbol*);

    void Push(SymTable*);

    void Pop();

    Symbol* Top();
};
