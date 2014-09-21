#include "generator.h"

//-----------------------------------------------------------------------------
AsmCmd::AsmCmd(AsmCmdType opcode_): opcode(opcode_) {}

AsmCmd::~AsmCmd() {}

//-----------------------------------------------------------------------------
AsmCmd1::AsmCmd1(AsmCmdType opcode, AsmArg* arg_): AsmCmd(opcode), arg(arg_) {}

AsmCmd1::~AsmCmd1() {}

//-----------------------------------------------------------------------------
AsmCmd2::AsmCmd2(AsmCmdType opcode, AsmArg* arg1_, AsmArg* arg2_):
    AsmCmd(opcode),
    arg1(arg1_),
    arg2(arg2_)
    {}

AsmCmd2::~AsmCmd2() {}

//-----------------------------------------------------------------------------
string AsmArg::Generate()
{
    return NULL;
}

bool AsmArg::operator == (int) const
{
    return false;
}

bool AsmArg::operator == (AsmArg*) const
{
    return false;
}

bool AsmArg::operator == (AsmRegName) const
{
    return false;
}

bool AsmArg::operator != (AsmArg* arg) const
{
    return !(*this == arg);
}

bool AsmArg::operator != (AsmRegName arg) const
{
    return !(*this == arg);
}

bool AsmArg::IsRegister() const
{
    return false;
}

bool AsmArg::UsesRegister(AsmRegName) const
{
    return false;
}

bool AsmArg::IsImmediate() const
{
    return false;
}

bool AsmArg::IsOffset() const
{
    return false;
}

void AsmArg::ClearOffset()
{

}

bool AsmArg::IsMemoryLocation() const
{
    return false;
}

//-----------------------------------------------------------------------------
AsmArgImmediate::AsmArgImmediate(int value_): value(value_) {}

AsmArgImmediate::~AsmArgImmediate() {}

string AsmArgImmediate::Generate()
{
    return to_string((long double)value);
}

bool AsmArgImmediate::operator == (int value_) const
{
    return value == value_;
}

bool AsmArgImmediate::IsImmediate() const
{
    return true;
}

//-----------------------------------------------------------------------------
AsmArgRegister::AsmArgRegister(AsmRegName reg_): reg(reg_) {}

AsmArgRegister::~AsmArgRegister() {}

string AsmArgRegister::Generate()
{
    return GetRegName();
}

string AsmArgRegister::GetRegName() const
{
    switch (reg)
    {
    case EAX:
        return "eax";
    case EBX:
        return "ebx";
    case ECX:
        return "ecx";
    case EDX:
        return "edx";
    case EBP:
        return "ebp";
    case ESP:
        return "esp";
    case CL:
        return "cl";
    case AL:
        return "al";
    case BL:
        return "bl";
    case AX:
        return "ax";
    default:
        throw exception("invalid register value");
    }
}

bool AsmArgRegister::operator == (AsmArg* arg) const
{
    AsmArgRegister* tmp = dynamic_cast<AsmArgRegister*>(arg);
    return tmp && tmp->reg == reg/* && !dynamic_cast<AsmArgIndirect*>(arg)*/;
}

bool AsmArgRegister::IsRegister() const
{
    return true;
}

bool AsmArgRegister::UsesRegister(AsmRegName reg_) const
{
    return reg == reg_;
}

//-----------------------------------------------------------------------------
AsmArgIndirect::AsmArgIndirect(AsmRegName reg_, int shift):
    AsmArgRegister(reg_),
    offset(shift)
    {}

AsmArgIndirect::~AsmArgIndirect() {}

string AsmArgIndirect::Generate()
{
    return "";
}

bool AsmArgIndirect::operator == (AsmArg* arg) const
{
    AsmArgIndirect* tmp = dynamic_cast<AsmArgIndirect*>(arg);
    return tmp && tmp->reg == reg && tmp->offset == offset;
}

bool AsmArgIndirect::operator == (AsmRegName) const
{
    return false;
}

bool AsmArgIndirect::IsMemoryLocation() const
{
    return true;
}

bool AsmArgIndirect::UsesRegister(AsmRegName reg_) const
{
    return reg == reg_;
}

//-----------------------------------------------------------------------------
AsmArgMemory::AsmArgMemory(const string& name_, bool lvalue_):
    name(name_),
    lvalue(lvalue_)
    {}

AsmArgMemory::~AsmArgMemory() {}

string AsmArgMemory::Generate()
{
    return (lvalue ? "offset " : "") + name;
}

bool AsmArgMemory::operator == (AsmArg* arg) const
{
    AsmArgMemory* tmp = dynamic_cast<AsmArgMemory*>(arg);
    return tmp && tmp->name == name;
}

bool AsmArgMemory::IsMemoryLocation() const
{
    return true;
}

bool AsmArgMemory::IsOffset() const
{
    return lvalue;
}

void AsmArgMemory::ClearOffset()
{
    lvalue = false;
}

//-----------------------------------------------------------------------------
AsmCode::AsmCode() {}

AsmCode::~AsmCode() {}

void AsmCode::AddCmd(AsmCmd* cmd)
{

}
