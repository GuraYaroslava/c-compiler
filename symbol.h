#pragma once

#include <vector>
#include "_parser_base.h"
#include "token.h"
#include "generator.h"
#include "statement_base.h"
#include "utils.h"

class Parser;
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
    virtual int GetByteSize() const;
    virtual void Print(int, ostream&);
    virtual void Generate(AsmCode&);
    virtual void Optimize(bool&, BaseParser&);
    virtual void SetUnUsed(BaseParser&);
};

//-----------------------------------------------------------------------------
class SymType: public Symbol
{
public:
    SymType(BaseToken*);
    ~SymType();

    virtual bool IsModifiableLvalue();
    virtual bool CanConvertTo(SymType*);

    virtual bool operator==(SymType*);
    virtual bool operator!=(SymType*);
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

    bool operator==(SymType*);

    int GetByteSize() const;
    void Print(int, ostream&);
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
    int GetByteSize() const;
    int GetShiftForBase();
    void Print(int, ostream&);
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

    bool operator==(SymType*);
    int GetByteSize() const;
    void Print(int, ostream&);
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

    bool operator==(SymType*);

    void Print(int, ostream&);
    void Generate(AsmCode&);
    void Optimize(bool&, BaseParser&);
    void SetUnUsed(BaseParser&);
};

//-----------------------------------------------------------------------------
class SymVar: public Symbol
{
protected:
    SymType* type;

public:
    friend class SymTable;

    bool local;
    int used;

    SymVar(BaseToken*, SymType*);
    SymVar(BaseToken*);
    ~SymVar();

    SymType* GetType();
    void SetType(SymType*);

    int GetByteSize() const;
    void Print(int, ostream&);
    void Generate(AsmCode&);
    void Optimize(bool&, BaseParser&);
    void SetUnUsed(BaseParser&);
};

//-----------------------------------------------------------------------------
class SymTable
{
public:
    int offset;
    int shift;

    vector <Symbol*> symbols;

    map <string, int> GetIndexByName;

    SymTable();
    ~SymTable();

    void SetUsed(const string&);
    void SetUnUsed(const string&);
    Symbol* Find(const string&);

    void Add(Symbol*);
    void Add(Symbol*, int);

    int GetSize();
    int GetByteSize();

    bool operator==(SymTable*);

    void Print(int, ostream&);

    void GenerateData(AsmCode&);
    void GenerateCode(AsmCode&);
    void Optimize(bool&, BaseParser&);
    void Delete(int);
};

//-----------------------------------------------------------------------------
class SymTableStack
{
public:
    vector <SymTable*> tables;

    SymTableStack();
    ~SymTableStack();

    void SetUsed(const string&);
    void SetUnUsed(const string&);
    Symbol* Find(const string&);

    void Add(Symbol*);
    void Add(Symbol*, int);

    void Push(SymTable*);

    void Pop();

    SymTable* Top();
};

extern SymTypeScalar* intType;
extern SymTypeScalar* floatType;
extern SymTypeScalar* charType;
