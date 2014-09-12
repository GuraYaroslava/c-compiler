#include "symbol.h"

Symbol::Symbol(BaseToken* name_): name(name_) {}

Symbol::~Symbol() {}

void Symbol::SymPrint(ostream& out)
{
    out << "`" << name->GetText() << "`";
}

SymType* Symbol::GetType()
{
    return NULL;
}

//-----------------------------------------------------------------------------
SymType::SymType(BaseToken* name): Symbol(name) {}

SymType::~SymType() {}

bool SymType::IsModifiableLvalue()
{
    return false;
}

bool SymType::CanConvertTo(SymType*)
{
    return false;
}

bool SymType::operator == (SymType* type_)
{
    return name == type_->name;
}

bool SymType::operator != (SymType* type_)
{
    return name != type_->name;
}

//-----------------------------------------------------------------------------
SymTypeScalar::SymTypeScalar(BaseToken* name): SymType(name) {}

SymTypeScalar::~SymTypeScalar() {}

bool SymTypeScalar::IsModifiableLvalue()
{
    return false;
}

bool SymTypeScalar::CanConvertTo(SymType* to)
{
    if (dynamic_cast<SymTypePointer*>(to)
        || dynamic_cast<SymTypeArray*>(to)
        || dynamic_cast<SymTypeFunc*>(to))
    {
        return false;
    }
    //return this->name->GetSubType() <= to->name->GetSubType() ? true : false;
    return true;
}

//-----------------------------------------------------------------------------
SymTypeArray::SymTypeArray(int size_, SymType* type_):
    SymType(NULL),
    type(type_),
    size(size_)
    {}

SymTypeArray::~SymTypeArray() {}

bool SymTypeArray::IsModifiableLvalue()
{
    return false;
}

bool SymTypeArray::CanConvertTo(SymType* to)
{
    //if (to == intType)
    //{
    //    return true;
    //}

    SymTypePointer* p = dynamic_cast<SymTypePointer*>(to);
    if (p && *p->refType == type)
    {
        return true;
    }

    return false;
}

bool SymTypeArray::operator == (SymType* type_)
{
    SymTypeArray* arr = dynamic_cast<SymTypeArray*>(type_);
    if (arr && *arr->type == type && arr->size == size)
    {
        return true;
    }

    return false;
}

void SymTypeArray::SymPrint(ostream &out)
{
    out << "array " << size << " of ";
    type->SymPrint(out);
}

//-----------------------------------------------------------------------------
SymTypePointer::SymTypePointer(SymType* type_): SymType(NULL), refType(type_) {}

SymTypePointer::~SymTypePointer() {}

bool SymTypePointer::IsModifiableLvalue()
{
    return true;
}

bool SymTypePointer::CanConvertTo(SymType* to)
{
    //if (to == intType)
    //{
    //    return true;
    //}

    SymTypePointer* pointer = dynamic_cast<SymTypePointer*>(to);
    if (pointer && *refType == pointer->refType)
    {
        return true;
    }

    SymTypeArray* arr = dynamic_cast<SymTypeArray*>(to);
    if (arr && *refType == arr->type)
    {
        return true;
    }

    return false;
}

bool SymTypePointer::operator == (SymType* type)
{
    SymTypePointer* pointer = dynamic_cast<SymTypePointer*>(type);
    if (!pointer)
    {
        return false;
    }

    SymType* type1 = refType;
    SymType* type2 = pointer->refType;

    if (type1 != type2)
    {
        return false;
    }

    return true;
}

void SymTypePointer::SymPrint(ostream& out)
{
    out << "pointer to ";
    refType->SymPrint(out);
}

//-----------------------------------------------------------------------------
SymTypeStruct::SymTypeStruct(BaseToken* name_, SymTable* fields_):
    SymType(name_),
    fields(fields_)
    {}

SymTypeStruct::~SymTypeStruct() {}

bool SymTypeStruct::IsModifiableLvalue()
{
    return false;
}

bool SymTypeStruct::CanConvertTo(SymType* to)
{
    SymTypeStruct* st = dynamic_cast<SymTypeStruct*>(to);
    if (!st || fields != st->fields)
    {
        return false;
    }

    return true;
}

void SymTypeStruct::SymPrint(ostream& out)
{
    out << "struct ";
    Symbol::SymPrint(out);
    if (fields->GetSize() > 0)
    {
        out << endl << "fields:" << endl;
        fields->Print(out);
    }
}

//-----------------------------------------------------------------------------
SymTypeFunc::SymTypeFunc(SymType* type_, SymTable* params_, StmtBlock* body_):
    SymType(NULL),
    type(type_),
    params(params_),
    body(body_)
    {};

SymTypeFunc::SymTypeFunc(SymType* type_):
    SymType(NULL),
    type(type_),
    params(new SymTable()),
    body(NULL)
    {};

SymTypeFunc::~SymTypeFunc() {}

bool SymTypeFunc::IsModifiableLvalue()
{
    return false;
}

bool SymTypeFunc::operator == (SymType* type)
{
    SymTypeFunc* func = dynamic_cast<SymTypeFunc*>(type);
    if (!func)
    {
        return false;
    }

    return *params == func->params && *type == func->type;
}

bool SymTypeFunc::CanConvertTo(SymType* to)
{
    return *this == to;
}

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

    out << " type of ";
    type->SymPrint(out);
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
    GetIndexByName[symbol->name->GetText()] = symbols.size()-1;
}

int SymTable::GetSize()
{
    return symbols.size();
}

bool SymTable::operator == (SymTable* table)
{
    if (GetSize() != table->GetSize())
    {
        return false;
    }

    for (int i = 0; i < GetSize(); ++i)
    {
        if (*dynamic_cast<SymVar*>(symbols[i])->type != dynamic_cast<SymVar*>(table->symbols[i])->type)
        {
            return false;
        }
    }

    return true;
}

void SymTable::Print(ostream& out)
{
    for (int i = 0, size = symbols.size(); i < size; ++i)
    {
        symbols[i]->SymPrint(out);
        out << endl;
    }
}

//-----------------------------------------------------------------------------
SymTableStack::SymTableStack(): tables(NULL) {}

SymTableStack::~SymTableStack() {}

void SymTableStack::Push(SymTable* table)
{
    tables.push_back(table);
}

void SymTableStack::Pop()
{
    tables.pop_back();
}

Symbol* SymTableStack::Find(const string& name)
{
    Symbol *symbol = 0;
    for (int i = tables.size() - 1; i >= 0 && !symbol; --i)
    {
        symbol = tables[i]->Find(name);
    }
    return symbol;
}

void SymTableStack::Add(Symbol* symbol)
{
    tables.back()->Add(symbol);
}

Symbol* SymTableStack::Top()
{
    SymTable *tbl = tables.back();
    int size = tbl->symbols.size();
    return tbl->symbols[size-1];
}
