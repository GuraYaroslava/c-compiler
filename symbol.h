#pragma once

#include <vector>

#include "token.h"

class SymTypeScalar;
class SymTypePointer;

extern SymTypeScalar* intType;
extern SymTypeScalar* floatType;
extern SymTypeScalar* charType;
extern SymTypePointer* stringType;

//-----------------------------------------------------------------------------
class SymType;

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

    virtual bool IsModifiableLvalue();
    virtual bool CanConvertTo(SymType*);

    virtual bool operator == (SymType*);
    virtual bool operator != (SymType*);
};

//-----------------------------------------------------------------------------
class SymTypeScalar: public SymType
{
public:
    SymTypeScalar(BaseToken*);
    ~SymTypeScalar();

    bool IsModifiableLvalue();
    bool CanConvertTo(SymType*);

    //void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypeArray: public SymType
{
public:
    int size;
    SymType* type;

    SymTypeArray(int, SymType*);
    ~SymTypeArray();

    bool IsModifiableLvalue();
    bool CanConvertTo(SymType*);

    bool operator == (SymType*);

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTable;

class SymTypeStruct: public SymType
{
public:
    SymTable* fields;

    SymTypeStruct(BaseToken*, SymTable*);
    ~SymTypeStruct();

    bool IsModifiableLvalue();
    bool CanConvertTo(SymType*);

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypePointer: public SymType
{
public:
    SymType* refType;

    SymTypePointer(SymType*);
    ~SymTypePointer();

    bool IsModifiableLvalue();
    bool CanConvertTo(SymType*);

    bool operator == (SymType*);

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class StmtBlock;

class SymTypeFunc: public SymType
{
public:
    SymType* type;
    SymTable* params;
    StmtBlock* body;

    SymTypeFunc(SymType*);
    SymTypeFunc(SymType*, SymTable*, StmtBlock*);
    ~SymTypeFunc();

    bool IsModifiableLvalue();
    bool CanConvertTo(SymType*);

    bool operator == (SymType*);

    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymVar: public Symbol
{
protected:
    SymType* type;

public:
    friend class SymTable;

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

    int GetSize();

    bool operator == (SymTable*);

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

    //SymTable* Top();
};

extern SymTypeScalar* intType;
extern SymTypeScalar* floatType;
extern SymTypeScalar* charType;
