#include "symbol.h"
#include "exception.h"

Symbol::Symbol(BaseToken* name_): name(name_), offset(0) {}

Symbol::~Symbol() {}

void Symbol::SetUnUsed(BaseParser&)
{

}

SymType* Symbol::GetType()
{
    return NULL;
}

int Symbol::GetByteSize() const
{
    return 0;
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

bool SymType::operator==(SymType* type_)
{
    return name->GetText() == type_->name->GetText();
}

bool SymType::operator!=(SymType* type_)
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

int SymTypeScalar::GetByteSize() const
{
    TokenType type = name->GetSubType();
    switch(type)
    {
    case CHAR:
        return 1;
    case INT:
        return 4;
    case FLOAT:
        return 4;
    }
    Exception(name->GetLine(), name->GetPosition(), "invalid type");
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
    if (p && *p->refType == type || *this == to)
    {
        return true;
    }

    return false;
}

bool SymTypeArray::operator==(SymType* type_)
{
    SymTypeArray* arr = dynamic_cast<SymTypeArray*>(type_);
    if (arr && *arr->type == type && arr->size == size)
    {
        return true;
    }

    return false;
}

int SymTypeArray::GetByteSize() const
{
    return type->GetByteSize() * size;
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

bool SymTypePointer::operator==(SymType* type)
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

int SymTypePointer::GetByteSize() const
{
    return 4;
}

//-----------------------------------------------------------------------------
SymTypeStruct::SymTypeStruct(BaseToken* name_):
    SymType(name_),
    fields(new SymTable())
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

int SymTypeStruct::GetByteSize() const
{
    return fields ? fields->GetByteSize() : 0;
}

int SymTypeStruct::GetShiftForBase()
{
    SymType* type = (*fields).symbols[0]->GetType();
    while (!dynamic_cast<SymTypeScalar*>(type))
    {
        if (dynamic_cast<SymTypeStruct*>(type))
        {
            type = (*dynamic_cast<SymTypeStruct*>(type)->fields).symbols[0]->GetType();
        }
        else if (dynamic_cast<SymTypeFunc*>(type))
        {
            type = dynamic_cast<SymTypeFunc*>(type)->type->GetType();
        }
        else if (dynamic_cast<SymTypePointer*>(type))
        {
            type = dynamic_cast<SymTypePointer*>(type)->refType->GetType();
        }
        else if (dynamic_cast<SymTypeArray*>(type))
        {
            type = dynamic_cast<SymTypeArray*>(type)->type->GetType();
        }
    }
    return type->GetByteSize();
}

//-----------------------------------------------------------------------------
SymTypeFunc::SymTypeFunc(SymType* type_, SymTable* params_, Statement* body_):
    SymType(NULL),
    type(type_),
    params(params_),
    body(body_),
    end(NULL)
    {};

SymTypeFunc::SymTypeFunc(SymType* type_):
    SymType(NULL),
    type(type_),
    params(new SymTable()),
    body(NULL),
    end(NULL)
    {};

SymTypeFunc::~SymTypeFunc() {}

void SymTypeFunc::SetUnUsed(BaseParser& parser)
{
    body->SetUnUsed(parser);
}

bool SymTypeFunc::IsModifiableLvalue()
{
    return false;
}

bool SymTypeFunc::operator==(SymType* type)
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

//-----------------------------------------------------------------------------
SymVar::SymVar(BaseToken* name_, SymType* type_):
    Symbol(name_),
    type(type_),
    local(false),
    used(0)
    {}

SymVar::SymVar(BaseToken* name_): Symbol(name_), type(NULL), local(false), used(false) {}

SymVar::~SymVar() {}

void SymVar::SetUnUsed(BaseParser& parser)
{
    if (dynamic_cast<SymTypeFunc*>(type))
    {
        type->SetUnUsed(parser);
    }
    --used;
}

SymType* SymVar::GetType()
{
    return type;
}

void SymVar::SetType(SymType* type_)
{
    type = type_;
}

int SymVar::GetByteSize() const
{
    return type->GetByteSize();
}

//-----------------------------------------------------------------------------
SymTable::SymTable(): symbols(NULL), offset(0), shift(0) {}

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

void SymTable::Add(Symbol* symbol, int flag)
{
    SymTable::Add(symbol);
    switch (flag)
    {
    case 0://locals
    {
        SymVar* vp = dynamic_cast<SymVar*>(symbol);
        if (vp)
        {
            SymType* type = vp->GetType();
            if (dynamic_cast<SymTypeArray*>(type))
            {
                symbol->offset = -(shift + offset + type->GetByteSize() - dynamic_cast<SymTypeArray*>(type)->type->GetByteSize());
            }
            else if (dynamic_cast<SymTypeStruct*>(type))
            {
                symbol->offset = -(shift + offset + type->GetByteSize() - dynamic_cast<SymTypeStruct*>(type)->GetShiftForBase());
            }
            else
            {
                symbol->offset = -(shift + offset);
            }
            offset += symbol->GetByteSize();
            vp->local = true;
        }
    }
        break;

    case 1://params
        if (dynamic_cast<SymTypeStruct*>(symbol->GetType()))
        {
            symbol->offset = offset + dynamic_cast<SymTypeStruct*>(symbol->GetType())->GetShiftForBase();
        }
        else
        {
            symbol->offset = offset + symbol->GetByteSize();
        }
        offset += symbol->GetByteSize();
        break;

    case 2://fields
        symbol->offset = offset;
        offset += symbol->GetByteSize();
        break;
    }
}

int SymTable::GetSize()
{
    return symbols.size();
}

int SymTable::GetByteSize()
{
    int bytes = 0;
    for (int i = 0, size = GetSize(); i < size; ++i)
    {
        bytes += symbols[i]->GetByteSize();
    }
    return bytes;
}

bool SymTable::operator==(SymTable* table)
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

void SymTable::SetUsed(const string& name)
{
    if (GetIndexByName.count(name) == 1)
    {
        dynamic_cast<SymVar*>(symbols[GetIndexByName.at(name)])->used += 1;
    }
}

void SymTable::SetUnUsed(const string& name)
{
    if (GetIndexByName.count(name) == 1)
    {
        dynamic_cast<SymVar*>(symbols[GetIndexByName.at(name)])->used -= 1;
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
    Symbol* symbol = NULL;
    for (int i = tables.size() - 1; i > -1 && !symbol; --i)
    {
        symbol = tables[i]->Find(name);
    }
    return symbol;
}

void SymTableStack::Add(Symbol* symbol)
{
    tables.back()->Add(symbol);
}

void SymTableStack::Add(Symbol* symbol, int flag)
{
    tables.back()->Add(symbol, flag);
}

SymTable* SymTableStack::Top()
{
    SymTable* tbl = tables.back();
    return tables.size() > 0 ? tables.back() : 0;
}

void SymTableStack::SetUsed(const string& name)
{
    Symbol* symbol = NULL;
    for (int i = tables.size() - 1; i > -1; --i)
    {
        tables[i]->SetUsed(name);
    }
}

void SymTableStack::SetUnUsed(const string& name)
{
    for (int i = tables.size() - 1; i > -1; --i)
    {
        tables[i]->SetUnUsed(name);
    }
}
