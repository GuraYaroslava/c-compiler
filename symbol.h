#pragma once

#include <iostream>
#include <vector>
#include "token.h"

class Parser;
class Symbol;
class SymType;
class StmtBlock;
class SymTypeRecord;
class SymTypePointer;

class SymTable
{
public:
    vector <Symbol*> symbols;
    map <string, int> index;

public:
    SymTable();
    Symbol* Find(const string&);
    void Add(Symbol*);
    void Print(ostream&);
};

class SymTableStack
{
public:
    vector <SymTable*> tables;

public:
    SymTableStack();
    Symbol *Find(const string&);
    Symbol *Top();
    void Add(Symbol*);
    void Push(SymTable*);
    void Pop();
};

class Symbol
{
protected:
    BaseToken* name;

public:
    Symbol(BaseToken*);
    Symbol(SymType*);
    ~Symbol();

    virtual void SymPrint(ostream&);
    virtual SymType* GetType();
    bool operator == (Symbol*);

    friend SymTypeRecord;
    friend SymTypePointer;
    friend SymTable;
    friend Parser;
};

//-----------------------------------------------------------------------------
class SymFunc: public Symbol
{
public:
    SymType* type;
    SymTable* args;
    StmtBlock* body;

public:
    SymFunc(BaseToken*, SymType*, SymTable*);
    ~SymFunc();

    void SymPrint(ostream&);
    SymType* GetType();
};

//-----------------------------------------------------------------------------
class SymType: public Symbol
{
public:
    BaseToken* type;

public:
    SymType(BaseToken*);
    SymType(SymType*);
    void SymPrint(ostream&);
    bool operator == (SymType*);
    bool operator != (SymType*);
};

//-----------------------------------------------------------------------------
class SymTypeScalar: public SymType
{
public:
    SymTypeScalar(BaseToken*);
};

class SymTypeChar: public SymTypeScalar
{
public:
    SymTypeChar(BaseToken*);
};

class SymTypeInteger: public SymTypeScalar
{
public:
    SymTypeInteger(BaseToken*);
}; 

class SymTypeDouble: public SymTypeScalar
{
public:
    SymTypeDouble(BaseToken*);
}; 

//-----------------------------------------------------------------------------
class SymTypeArray: public SymType
{
private:
    SymType* elemType;
    vector <int> sizes;

public:
    SymTypeArray(SymType*);
    ~SymTypeArray();

    void AddLevel(int);
    void SymPrint(ostream&);
};

class SymTypeRecord: public SymType
{
private:
    SymTable* fields;

public:
    SymTypeRecord(Symbol*);
    SymTypeRecord(BaseToken*, SymTable*);
    SymTypeRecord(SymType*, SymTable*);
    ~SymTypeRecord();

    void SymPrint(ostream&);
    friend SymTable;
    friend Parser;
};

class SymTypePointer: public SymType
{
public:
    Symbol* refType;

public:
    SymTypePointer(SymType*);
    SymTypePointer(Symbol*);
    ~SymTypePointer();

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymVar: public Symbol
{
private:
    SymType* type;

public:
    SymVar(BaseToken*, SymType*);
    ~SymVar();

    virtual void SymPrint(ostream&);
    SymType* GetType();
};

class SymVarConst: public SymVar
{
public:
    SymVarConst(BaseToken*, SymType*);
    ~SymVarConst();
};

class SymVarParam: public SymVar
{
public:
    SymVarParam(BaseToken*, SymType*);
    ~SymVarParam();
    void SymPrint(ostream&);
};

// когда их создавать, кто знает?
class SymVarLocal: public SymVar
{
public:
    SymVarLocal(BaseToken*, SymType*);
    ~SymVarLocal();
};

class SymVarGlobal: public SymVar
{
public:
    SymVarGlobal(BaseToken*, SymType*);
    ~SymVarGlobal();
};