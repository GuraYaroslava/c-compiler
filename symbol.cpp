#include "symbol.h"

//-----------------------------------------------------------------------------
Symbol::Symbol(BaseToken* name_): name(name_) {} // name of variable

Symbol::~Symbol() {}

void Symbol::SymPrint(ostream& out)
{
    out << name->GetText();
}

SymType* Symbol::GetType()
{
    return NULL;
}

//-----------------------------------------------------------------------------
SymType::SymType(BaseToken* name): Symbol(name) {} // name of type

SymType::~SymType() {}

//-----------------------------------------------------------------------------
SymTypeScalar::SymTypeScalar(BaseToken* name): SymType(name) {} // name of type

//-----------------------------------------------------------------------------
SymTypeArray::SymTypeArray(int size_, SymType* type_): SymType(NULL), type(type_), size(size_) {}

SymTypeArray::~SymTypeArray() {}

void SymTypeArray::SymPrint(ostream &out)
{
    out << "array " << size << " of ";
    type->SymPrint(out);
}

//-----------------------------------------------------------------------------
SymTypePointer::SymTypePointer(SymType* type_): SymType(NULL), refType(type_) {}

void SymTypePointer::SymPrint(ostream& out)
{
    out << "pointer to ";
    refType->SymPrint(out);
}

//-----------------------------------------------------------------------------
SymTypeStruct::SymTypeStruct(BaseToken* name_, SymTable* fields_):
    SymType(name_), // name of type
    fields(fields_)
    {}

void SymTypeStruct::SymPrint(ostream& out)
{
    out << "struct ";
    Symbol::SymPrint(out);
    fields->Print(out);
}

//-----------------------------------------------------------------------------
SymTypeFunc::SymTypeFunc(SymType* type_, SymTable* params_, StmtBlock* body_):
    SymType(NULL),
    type(type_),
    params(params_),
    body(body_) {};

SymTypeFunc::~SymTypeFunc() {}

void SymTypeFunc::SymPrint(ostream& out)
{
    out << "function(";

    if (!params->symbols.empty())
    {
        int size = params->symbols.size()-1;
        for (int i = 0; i < size; ++i)
        {
            params->symbols[i]->SymPrint(out);
            out << ", ";
        }
        params->symbols[size]->SymPrint(out);
    }

    out << ") returning ";
    type->SymPrint(out);

    //if (body)
    //{
    //    out << endl;
    //    body->StmtPrint(out);
    //}
}

//-----------------------------------------------------------------------------
SymVar::SymVar(BaseToken* name_, SymType* type_): Symbol(name_), type(type_) {}
SymVar::SymVar(BaseToken* name_): Symbol(name_), type(NULL) {}

SymVar::~SymVar() {}

SymType* SymVar::GetType()
{
    return type;
}

void SymVar::SetType(SymType* type_)
{
	type = type_;
}

void SymVar::SymPrint(ostream& out)
{
    out << "variable ";
    Symbol::SymPrint(out);

    out << "type of ";
    type->SymPrint(out);
    out << endl;
};

//-----------------------------------------------------------------------------
SymTable::SymTable(): symbols(NULL) {}

SymTable::~SymTable() {}

Symbol* SymTable::Find(const string& name)
{
    return GetIndexByName.count(name) == 1 ? symbols[GetIndexByName.at(name)] : NULL;
}

void SymTable::Add(Symbol* symbol)
{
    symbols.push_back(symbol);
    GetIndexByName[symbol->name->GetText()] = symbols.size() - 1;
}

void SymTable::Print(ostream& out)
{
    for (int i = 0; i < symbols.size(); ++i)
    {
        symbols[i]->SymPrint(out);
        out << endl;
    }
}

//-----------------------------------------------------------------------------
SymTableStack::SymTableStack(): tables(NULL) {}

void SymTableStack::Push(SymTable *table)
{
    tables.push_back(table);
}

void SymTableStack::Pop()
{
    tables.pop_back();
}

Symbol *SymTableStack::Find(const string &name)
{
    Symbol *symbol = 0;
    for (int i = tables.size() - 1; i >= 0 && !symbol; --i)
        symbol = tables[i]->Find(name);
    return symbol;
}

void SymTableStack::Add(Symbol *symbol)
{
    tables.back()->Add(symbol);
}

Symbol *SymTableStack::Top() 
{
    SymTable *tbl = tables.back();
    int size = tbl->symbols.size();
    return tbl->symbols[size-1];
}