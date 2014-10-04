#pragma once

#include <vector>

#include "token.h"
#include "generator.h"
#include "statement_base.h"
#include "utils.h"

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

    int offset;

    Symbol(BaseToken*);
    ~Symbol();

    virtual SymType* GetType();
    virtual void Generate(AsmCode&);
    virtual void SymPrint(ostream&);
    virtual int GetByteSize() const;
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
    int GetByteSize() const;
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

    SymTypeStruct(BaseToken*);
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
    int GetByteSize() const;
    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTypeFunc: public SymType
{
public:
    SymType* type;
    SymTable* params;
    Statement* body;
    AsmArgLabel* end;

    SymTypeFunc(SymType*);
    SymTypeFunc(SymType*, SymTable*, Statement*);
    ~SymTypeFunc();

    bool IsModifiableLvalue();
    bool CanConvertTo(SymType*);

    bool operator == (SymType*);

    void SymPrint(ostream&);
    void Generate(AsmCode&);
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

    int GetByteSize() const;
    SymType* GetType();
    void SetType(SymType*);
    void Generate(AsmCode&);
    void SymPrint(ostream&);
};

//-----------------------------------------------------------------------------
class SymTable
{
public:
    int offset;

    vector <Symbol*> symbols;

    map <string, int> GetIndexByName;

    SymTable();
    ~SymTable();

    Symbol* Find(const string&);

    void Add(Symbol*);

    int GetSize();
    int GetByteSize();

    bool operator == (SymTable*);

    void Print(ostream&);

    void GenerateData(AsmCode&);
    void GenerateCode(AsmCode&);
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

    SymTable* Top();
};

extern SymTypeScalar* intType;
extern SymTypeScalar* floatType;
extern SymTypeScalar* charType;
