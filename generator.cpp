#include <fstream>
#include <sstream>

#include "generator.h"
#include "exception.h"

string AsmCmd::Generate()
{
    return "";
}

//-----------------------------------------------------------------------------
AsmRowCmd::AsmRowCmd(string str_): str(str_) {}

AsmRowCmd::~AsmRowCmd() {}

//-----------------------------------------------------------------------------
AsmCmd0::AsmCmd0(AsmCmdName opcode_): opcode(opcode_) {}

AsmCmd0::~AsmCmd0() {}

string AsmCmd0::Generate()
{
    return AsmCmdNameToString(opcode);
}

//-----------------------------------------------------------------------------
AsmCmd1::AsmCmd1(AsmCmdName opcode, AsmArg* arg_): AsmCmd0(opcode), arg(arg_) {}

AsmCmd1::~AsmCmd1() {}

AsmArg* AsmCmd1::GetArgument()
{
    return arg;
}

bool AsmCmd1::operator==(AsmCmdName cmd)
{
    return opcode == cmd;
}

string AsmCmd1::Generate()
{
    return AsmCmdNameToString(opcode)
        + (dynamic_cast<AsmArgImmediate*>(arg) && opcode != cmdRET ? " dword ptr " : " ")
        + arg->Generate();
}

//-----------------------------------------------------------------------------
AsmCmd2::AsmCmd2(AsmCmdName opcode, AsmArg* arg1_, AsmArg* arg2_):
    AsmCmd0(opcode),
    arg1(arg1_),
    arg2(arg2_)
    {}

AsmCmd2::~AsmCmd2() {}

bool AsmCmd2::operator==(AsmCmdName cmd)
{
    return opcode == cmd;
}

AsmArg* AsmCmd2::GetFirst()
{
    return arg1;
}

AsmArg* AsmCmd2::GetSecond()
{
    return arg2;
}

string AsmCmd2::Generate()
{
    return opcode > cmdDQ
        ? AsmCmdNameToString(opcode) + " " + arg1->Generate() + ", " + arg2->Generate()
        : arg1->Generate() + " " + AsmCmdNameToString(opcode) + " " + arg2->Generate();
}

//-----------------------------------------------------------------------------
AsmArg::AsmArg() {}

AsmArg::~AsmArg() {}

string AsmArg::Generate()
{
    return "0";
}

bool AsmArg::operator==(int) const
{
    return false;
}

bool AsmArg::operator==(string) const
{
    return false;
}

bool AsmArg::operator==(AsmArg*) const
{
    return false;
}

bool AsmArg::operator==(AsmRegName) const
{
    return false;
}

bool AsmArg::operator!=(AsmArg* arg) const
{
    return !(*this == arg);
}

bool AsmArg::operator!=(AsmRegName arg) const
{
    return !(*this == arg);
}

//-----------------------------------------------------------------------------
AsmArgImmediate::AsmArgImmediate(int value_): AsmArg(), value(value_) {}

AsmArgImmediate::~AsmArgImmediate() {}

string AsmArgImmediate::Generate()
{
    return to_string((long double)value);
}

bool AsmArgImmediate::operator==(int value_) const
{
    return value == value_;
}

bool AsmArgImmediate::operator==(string value_) const
{
    return to_string((long double)value) == value_;
}

//-----------------------------------------------------------------------------
AsmArgRegister::AsmArgRegister(AsmRegName reg_): AsmArg(), reg(reg_) {}

AsmArgRegister::~AsmArgRegister() {}

string AsmArgRegister::Generate()
{
    return RegNameToString();
}

bool AsmArgRegister::operator!=(AsmArg* arg) const
{
    if (dynamic_cast<AsmArgRegister*>(arg) && !dynamic_cast<AsmArgIndirect*>(arg))
    {
        return reg != dynamic_cast<AsmArgRegister*>(arg)->reg;
    }
    return true;
}

bool AsmArgRegister::operator!=(AsmRegName arg) const
{
    return reg != arg;
}

string AsmArgRegister::RegNameToString() const
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
    case ST0:
        return "st";
    case ST1:
        return "st(1)";
    default:
        throw exception("invalid register value");
    }
}

bool AsmArgRegister::operator==(string arg) const
{
    return RegNameToString() == arg;
}

bool AsmArgRegister::operator==(AsmArg* arg) const
{
    AsmArgRegister* tmp = dynamic_cast<AsmArgRegister*>(arg);
    return tmp && tmp->reg == reg && !dynamic_cast<AsmArgIndirect*>(arg);
}

bool AsmArgRegister::operator==(AsmRegName arg) const
{
    return reg == arg;
}

//-----------------------------------------------------------------------------
AsmArgIndirect::AsmArgIndirect(AsmRegName reg_, int shift):
    AsmArgRegister(reg_),
    offset(shift)
    {}

AsmArgIndirect::~AsmArgIndirect() {}

string AsmArgIndirect::Generate()
{
    return "dword ptr [" + RegNameToString() + " + " + to_string((long double)offset) + "]";
}

bool AsmArgIndirect::operator==(AsmArg* arg) const
{
    AsmArgIndirect* tmp = dynamic_cast<AsmArgIndirect*>(arg);
    return tmp && tmp->reg == reg && tmp->offset == offset;
}

bool AsmArgIndirect::operator==(AsmRegName) const
{
    return false;
}

bool AsmArgIndirect::usesRegister(AsmArg* arg) const
{
    AsmArgRegister* tmp = dynamic_cast<AsmArgRegister*>(arg);
    return tmp && tmp->reg == reg;
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

bool AsmArgMemory::operator==(string arg) const
{
    return name == name;
}

bool AsmArgMemory::operator==(AsmArg* arg) const
{
    AsmArgMemory* tmp = dynamic_cast<AsmArgMemory*>(arg);
    return tmp && tmp->name == name;
}

//-----------------------------------------------------------------------------
AsmArgDup::AsmArgDup(int size_): size(size_) {}

AsmArgDup::~AsmArgDup() {}

string AsmArgDup::Generate()
{
    return to_string((long double)size) + " dup(0)";
}

//-----------------------------------------------------------------------------
AsmLabel::AsmLabel(string label_): label(new AsmArgLabel(label_)) {}

AsmLabel::AsmLabel(AsmArgLabel* label_): label(label_) {}

AsmLabel::~AsmLabel() {}

string AsmLabel::Generate()
{
    return label->Generate() + ":";
}

//-----------------------------------------------------------------------------
AsmArgLabel::AsmArgLabel(string name_): name(name_) {}

AsmArgLabel::~AsmArgLabel() {}

string AsmArgLabel::Generate()
{
    return name;
}

//-----------------------------------------------------------------------------
AsmArgString::AsmArgString(string val_): val(val_) {}

AsmArgString::~AsmArgString() {}

string AsmArgString::Generate()
{
    return val;
}

//-----------------------------------------------------------------------------
AsmArgFloat::AsmArgFloat(float val_): val(val_) {}

AsmArgFloat::~AsmArgFloat() {}

string AsmArgFloat::Generate()
{
    std::ostringstream buff;
    buff << fixed << val;
    return buff.str();
}

{
}

//-----------------------------------------------------------------------------
AsmCmdPrint::AsmCmdPrint(AsmArgMemory* format_):
    AsmCmd0(cmdINVOKE),
    format(format_)
    {}

AsmCmdPrint::~AsmCmdPrint() {}

string AsmCmdPrint::Generate()
{
    return AsmCmdNameToString(opcode) + " crt_printf, addr " + format->Generate();
}

//-----------------------------------------------------------------------------
AsmCode::AsmCode() {}

AsmCode::~AsmCode() {}

void AsmCode::AddCmd(string row)
{

}

void AsmCode::AddCmd(AsmCmd* cmd)
{
    cmds.push_back(cmd);
}

void AsmCode::AddCmd(AsmCmdName cmd)
{
    cmds.push_back(new AsmCmd0(cmd));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmArg* arg)
{
    cmds.push_back(new AsmCmd1(cmd, arg));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmArg* arg1, AsmArg* arg2)
{
    cmds.push_back(new AsmCmd2(cmd, arg1, arg2));
}

void AsmCode::AddCmd(AsmArgMemory* format)
{
    cmds.push_back(new AsmCmdPrint(format));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmLabel* label)
{
    cmds.push_back(new AsmCmd1(cmd, label->label));
}

void AsmCode::AddCmd(AsmLabel* label)
{
    cmds.push_back(label);
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmRegName reg, int size)
{
    cmds.push_back(new AsmCmd2(cmd, new AsmArgRegister(reg), new AsmArgImmediate(size)));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmRegName reg)
{
    cmds.push_back(new AsmCmd1(cmd, new AsmArgRegister(reg)));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmRegName reg1, AsmRegName reg2)
{
    cmds.push_back(new AsmCmd2(cmd, new AsmArgRegister(reg1), new AsmArgRegister(reg2)));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmRegName arg1, AsmArg* arg2)
{
    cmds.push_back(new AsmCmd2(cmd, new AsmArgRegister(arg1), arg2));
}

void AsmCode::AddCmd(AsmCmdName cmd, AsmArg* arg1, AsmRegName arg2)
{
    cmds.push_back(new AsmCmd2(cmd, arg1, new AsmArgRegister(arg2)));
}

void AsmCode::AddCmd(AsmArgLabel* label)
{
    cmds.push_back(new AsmLabel(label));
}

//-----------------------------------------------------------------------------
Generator::Generator(const string& file): filename(file) {}

Generator::~Generator() {};

void Generator::Generate()
{
    ofstream out(filename);
    if (!out)
    {
        throw exception("Cannot open file");
    }

    out << ".686\n"

           ".model flat, stdcall\n"

           "include c:\\masm32\\include\\msvcrt.inc\n"
           "includelib c:\\masm32\\lib\\msvcrt.lib\n"

           "\n.data\n";

    for (int i = 0, size = data.cmds.size(); i < size; ++i)
    {
        out << (dynamic_cast<AsmLabel*>(data.cmds[i]) ? "" : "    ") << data.cmds[i]->Generate() << endl;
    }
    out << "\n.code\n";

    for (int i = 0, size = code.cmds.size(); i < size; ++i)
    {
        out << (dynamic_cast<AsmLabel*>(code.cmds[i]) ? "" : "    ") << code.cmds[i]->Generate() << endl;
    }
    out << "end start";
}

AsmArgString* GenAsmString(const string& val)
{
    string str(val);
    for (int i = 0; i < str.length() - 2; ++i)
        if (str.substr(i, 2) == "\\n")
        {
            string str1(str.substr(0, i)), str2(str.substr(i + 2));
            str = str1 + "\", 0dh, 0ah";
            if (str2.length() > 1)
                str += ", \"" + str2;
        }
    str += ", 0";
    return new AsmArgString(str);
}

string AsmCmdNameToString(AsmCmdName opcode)
{
    switch (opcode)
    {
    case cmdREAL4:
        return "real4";
    case cmdREAL8:
        return "real8";
    case cmdMOV:
        return "mov";
    case cmdPUSH:
        return "push";
    case cmdPOP:
        return "pop";
    case cmdMUL:
        return "mul";
    case cmdIMUL:
        return "imul";
    case cmdDIV:
        return "div";
    case cmdIDIV:
        return "idiv";
    case cmdADD:
        return "add";
    case cmdSUB:
        return "sub";
    //case cmdINC:
        //return "inc";
    //case cmdDEC:
        //return "dec";
    case cmdRET:
        return "ret";
    case cmdDB:
        return "db";
    case cmdDD:
        return "dd";
    case cmdDQ:
        return "dq";
    case cmdINVOKE:
        return "invoke";
    case cmdXOR:
        return "xor";
    case cmdNEG:
        return "neg";
    case cmdCDQ:
        return "cdq";
    case cmdSHL:
        return "shl";
    case cmdSHR:
        return "shr";
    case cmdAND:
        return "and";
    case cmdOR:
        return "or";
    case cmdNOT:
        return "not";
    case cmdCALL:
        return "call";
    case cmdJMP:
        return "jmp";
    case cmdCMP:
        return "cmp";
    case cmdJE:
        return "je";
    case cmdJNE:
        return "jne";
    case cmdSETE:
        return "sete";
    case cmdSETNE:
        return "setne";
    case cmdSETB:
        return "setb";
    case cmdSETBE:
        return "setbe";
    case cmdSETA:
        return "seta";
    case cmdSETAE:
        return "setae";
    case cmdSETG:
        return "setg";
    case cmdSETGE:
        return "setge";
    case cmdSETL:
        return "setl";
    case cmdSETLE:
        return "setle";
    case cmdFADDP:
        return "faddp";
    case cmdFDIVP:
        return "fdivp";
    case cmdFMULP:
        return "fmulp";
    case cmdFSUBP:
        return "fsubp";
    case cmdFLD:
        return "fld";
    case cmdFSTP:
        return "fstp";
    case cmdFCHS:
        return "fchs";
    case cmdFILD:
        return "fild";
    case cmdFISTP:
        return "fistp";
    case cmdFLD1:
        return "fld1";
    case cmdFCOMPP:
        return "fcompp";
    case cmdFNSTSW:
        return "fnstsw";
    case cmdSAHF:
        return "sahf";
    default:
        throw Exception("invalid cmd");
    }
}
