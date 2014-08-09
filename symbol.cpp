#include <iomanip>
#include "symbol.h"
#include "statement.h"

SymTable::SymTable(): symbols(NULL) {}

Symbol *SymTable::Find(const string &name)
{
    return index.count(name) == 1 ? symbols[index.at(name)] : NULL;
}

void SymTable::Add(Symbol* symbol)
{
    symbols.push_back(symbol);
    index[symbol->name->GetText()] = symbols.size() - 1;    //проверить
}

//-----------------------------------------------------------------------------
Symbol::Symbol(BaseToken* name_): name(name_) {}

Symbol::Symbol(SymType *type_): name(dynamic_cast <Symbol*>(type_)->name) {}

Symbol::~Symbol()
{
    delete name;
    name = NULL;
}

void Symbol::SymPrint(ostream &out)
{
    out << name->GetText();
}

SymType* Symbol::GetType()
{
    return NULL;
}

bool Symbol::operator == (Symbol* s)
{
    /*if (/*!strcmp(&name->GetText()[0], &s->name->GetText()[0]) &&*/
        /*this->GetType() == s->GetType()) 
        return true;*/
    return false;
}

//-----------------------------------------------------------------------------
SymType::SymType(BaseToken* type_): Symbol(type_), type(type_) {}

SymType::SymType(SymType* type_): Symbol(type_->type), type(type_->type) {}

void SymType::SymPrint(ostream &out)
{
    Symbol::SymPrint(out);
}

bool SymType::operator == (SymType* right)
{
    if ((dynamic_cast <SymTypeInteger*> (this) || dynamic_cast <SymTypeChar*> (this) || dynamic_cast <SymTypeDouble*> (this)) &&
        (dynamic_cast <SymTypeInteger*> (right) || dynamic_cast <SymTypeChar*> (right) || dynamic_cast <SymTypeDouble*> (right)))
        return true;
    if (dynamic_cast <SymTypePointer*> (this) && dynamic_cast <SymTypePointer*> (right))
    {
        SymTypePointer *left = dynamic_cast <SymTypePointer*> (this);
        SymTypePointer *right = dynamic_cast <SymTypePointer*> (right);
        if (left->refType == right->refType)
            return true;
    }
    return false;
}

bool SymType::operator != (SymType* right)
{
    //SymType *left = new SymType (this);
    cout << "////////////" << endl
         << /*this->type->GetText () << endl <<*/ endl << right->type->GetText() << endl << "/////////////////////" << endl;
    cout << "////////////" << endl
         << this->type->tokenTypeToString[this->type->GetType()] << endl << endl
         << right->type->tokenTypeToString[right->type->GetType()] << endl << "/////////////////////" << endl;

    bool res = true;
    /*if (static_cast <SymTypeInteger*> (this) && dynamic_cast <SymTypeInteger*> (right))
        res = false;
    if (static_cast <SymTypeDouble*> (this) && dynamic_cast <SymTypeDouble*> (right))
        res = false;
    if (static_cast <SymTypeChar*> (this) && dynamic_cast <SymTypeChar*> (right))
        res = false;*/

    if (static_cast <SymTypeInteger*> (this) && dynamic_cast <SymTypeInteger*> (right))
        res = false;
    if (static_cast <SymTypeInteger*> (this) && dynamic_cast <SymTypeDouble*> (right))
        res = false;
    if (static_cast <SymTypeInteger*> (this) && dynamic_cast <SymTypeChar*> (right))
        res = false;
    if (static_cast <SymTypeChar*> (this) && dynamic_cast <SymTypeInteger*> (right))
        res = false;
    if (static_cast <SymTypeChar*> (this) && dynamic_cast <SymTypeDouble*> (right))
        res = false;
    if (static_cast <SymTypeChar*> (this) && dynamic_cast <SymTypeChar*> (right))
        res = false;
    if (static_cast <SymTypeDouble*> (this) && dynamic_cast <SymTypeInteger*> (right))
        res = false;
    if (static_cast <SymTypeDouble*> (this) && dynamic_cast <SymTypeDouble*> (right))
        res = false;
    if (static_cast <SymTypeDouble*> (this) && dynamic_cast <SymTypeChar*> (right))
        res = false;
    if (static_cast <SymTypeRecord*> (this) && dynamic_cast <SymTypeRecord*> (right))
        res = false;

    /*if ((static_cast <SymTypeInteger*> (this) || static_cast <SymTypeChar*> (this) || static_cast <SymTypeDouble*> (this)) && 
            (dynamic_cast <SymTypeInteger*> (right) || dynamic_cast <SymTypeChar*> (right) || dynamic_cast <SymTypeDouble*> (right)))
            res = false;*/

    else if (static_cast <SymTypePointer*> (this))
    {
        if (dynamic_cast <SymTypePointer*> (right))
        {
            /*SymTypePointer *left = dynamic_cast <SymTypePointer*> (this);
            SymTypePointer *right = dynamic_cast <SymTypePointer*> (right);
            if (left->refType == right->refType)
                return true;*/
            res = false;
        }
        else res = true;
    }
    return res;
}

//-----------------------------------------------------------------------------
SymTypeScalar::SymTypeScalar (BaseToken* type_): SymType(type_) {}

SymTypeChar::SymTypeChar(BaseToken* type_): SymTypeScalar(type_) {}
SymTypeInteger::SymTypeInteger(BaseToken* type_): SymTypeScalar(type_) {}
SymTypeDouble::SymTypeDouble(BaseToken* type_): SymTypeScalar(type_) {}

//-----------------------------------------------------------------------------
SymTypeArray::SymTypeArray(SymType* type_): SymType(type_), elemType(type_), sizes(NULL) {}

void SymTypeArray::AddLevel(int size_)
{
    sizes.push_back(size_);
}

void SymTypeArray::SymPrint(ostream &out)
{
    out << "array of ";
    elemType->SymPrint(out);
}

//-----------------------------------------------------------------------------
SymTypePointer::SymTypePointer(SymType* type_): SymType(type_), refType(type_) {}

SymTypePointer::SymTypePointer(Symbol* type_): SymType(type_->name), refType(type_) {}

void SymTypePointer::SymPrint(ostream &out)
{
    out << "pointer to ";
    refType->SymPrint(out);
}

//-----------------------------------------------------------------------------
SymTypeRecord::SymTypeRecord(BaseToken* type_, SymTable* fields_): SymType(type_), fields(fields_) {}

SymTypeRecord::SymTypeRecord(SymType* type_, SymTable* fields_): SymType(type_), fields(fields_) {}

SymTypeRecord::SymTypeRecord(Symbol *_symbol):
    SymType (dynamic_cast <SymTypeRecord*> (_symbol)->name),
    fields(dynamic_cast <SymTypeRecord*> (_symbol)->fields) {};

void SymTypeRecord::SymPrint(ostream &out) 
{
    out << "struct "; 
    Symbol::SymPrint(out);
}

//-----------------------------------------------------------------------------
SymVar::SymVar(BaseToken* name_, SymType* type_): Symbol(name_), type(type_) {}

SymVar::~SymVar()
{
    delete type;
    type = NULL;
}

SymType *SymVar::GetType()
{
    return type;
}

void SymVar::SymPrint(ostream &out) 
{
    //out << setw(20);
    out << "Name: ";
    Symbol::SymPrint(out);
    //out << setw(20);
    out << endl << "Type: ";
    type->SymPrint(out);
    out << endl;    
};

//-----------------------------------------------------------------------------
SymVarConst::SymVarConst(BaseToken* name_, SymType* type_): SymVar(name_, type_) {}

//-----------------------------------------------------------------------------
SymVarParam::SymVarParam(BaseToken* name_, SymType* type_): SymVar(name_, type_) {}

void SymVarParam::SymPrint(ostream &out) {SymVar::SymPrint(out);}

//-----------------------------------------------------------------------------
SymVarLocal::SymVarLocal(BaseToken* name_, SymType* type_): SymVar(name_, type_) {}

//-----------------------------------------------------------------------------
SymVarGlobal::SymVarGlobal(BaseToken* name_, SymType* type_): SymVar(name_, type_) {}

//-----------------------------------------------------------------------------
SymFunc::SymFunc(BaseToken* name_, SymType* type_, SymTable *_args):
    Symbol(name_),
    type(type_),
    args(_args),
    //locals(NULL),
    body(NULL) {};

SymFunc::~SymFunc()
{
    delete type;
    type = NULL;
}

SymType* SymFunc::GetType()
{
    return type;
}

void SymFunc::SymPrint(ostream &out)
{
    //out << setw(20);
    out << "Name: ";
    Symbol::SymPrint(out);
    //out << setw(30);
    out << endl << "Type: ";
    out << "function returing ";
    type->SymPrint(out);
    if (!args->symbols.empty()) 
    {
        out << endl;
        out << "Arguments_begin" << endl;
        args->Print(out);
        out << "Arguments_end:" << endl;
    }
    if (body) {out << endl; body->StmtPrint(out);}
}

//-----------------------------------------------------------------------------
void SymTable::Print(ostream &out)
{
    /*out << "+=============================================================================+" << endl;
    out << setw(20) << "Name";
    out << setw(30) << "Type" << endl;
    out << "+=============================================================================+" << endl;*/
    for (int i = 0; i < symbols.size(); ++i)
    {
        if (dynamic_cast <SymTypeRecord*> (symbols[i]))
        {
            //out << setw(20);
            out << "Type: struct "; 
            out << symbols[i]->name->GetText();
            if (dynamic_cast <SymTypeRecord*> (symbols[i])->fields->symbols.empty())
            {
                out << " (No fields)" << endl << endl;
                continue;
            }
            out << endl << "Fields_begin" << endl;
            dynamic_cast <SymTypeRecord*> (symbols[i])->fields->Print(out);
            out << endl << "Fields_end" << endl;
        }
        else
            symbols[i]->SymPrint(out);
        out << endl << endl;
    }
    //out << "+=============================================================================+" << endl;
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