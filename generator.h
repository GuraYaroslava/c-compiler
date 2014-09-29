#pragma once

#include <vector>
#include "token.h"
using namespace std;

typedef enum
{
    //cmdREAL4,
    //cmdREAL8,

    //cmdDD,
    //cmdDB,
    //cmdDQ,

    cmdMOV,

    cmdPUSH,
    cmdPOP,

    cmdMUL,
    cmdIMUL,

    cmdDIV,
    cmdIDIV,

    cmdADD,
    cmdSUB,

    //cmdINC,
    //cmdDEC,

    cmdRET,
    cmdNEG,
    cmdCDQ,
    cmdINVOKE,

    cmdSHR,
    cmdSHL,

    cmdAND,
    cmdOR,
    cmdXOR,
    cmdNOT,

    cmdCALL,
    cmdJMP,
    cmdCMP,
    cmdJE,
    cmdJNE,

    cmdSETG,
    cmdSETL,
    cmdSETGE,
    cmdSETLE,
    cmdSETE,
    cmdSETNE,

    cmdFDIVP,
    cmdFADDP,
    cmdFMULP,
    cmdFSUBP,
    cmdFLD,
    cmdFSTP,
    cmdFCHS,
    cmdFILD,
    cmdFISTP,
    cmdFLD1,
    cmdFCOMPP,
    cmdFNSTSW,
    cmdSAHF,
} AsmCmdName;

typedef enum
{
    EAX,
    EBX,
    ECX,
    EDX,
    EBP,
    ESP,
    CL,
    AL,
    BL,
    AX,
} AsmRegName;

//-----------------------------------------------------------------------------
class AsmCmd
{
protected:
    AsmCmdType opcode;

public:
    AsmCmd(AsmCmdType);
    ~AsmCmd();
};

//-----------------------------------------------------------------------------
class AsmArg;

class AsmCmd1: public AsmCmd
{
private:
    AsmArg* arg;

public:
    AsmCmd1(AsmCmdType, AsmArg*);
    ~AsmCmd1();
};

//-----------------------------------------------------------------------------
class AsmCmd2: public AsmCmd
{
private:
    AsmArg *arg1, *arg2;

public:
    AsmCmd2(AsmCmdType, AsmArg*, AsmArg*);
    ~AsmCmd2();
};

//-----------------------------------------------------------------------------
class AsmArgRegister;

class AsmArg
{
public:
    virtual string Generate();

    virtual bool operator == (int) const;
    virtual bool operator == (AsmArg*) const;
    virtual bool operator == (AsmRegName) const;

    bool operator != (AsmArg*) const;
    bool operator != (AsmRegName) const;

    virtual bool IsRegister() const;
    virtual bool UsesRegister(AsmRegName) const;

    virtual bool IsMemoryLocation() const;

    virtual bool IsImmediate() const;

    virtual bool IsOffset() const;
    virtual void ClearOffset();
};

//-----------------------------------------------------------------------------
class AsmArgImmediate: public AsmArg
{
private:
    int value;

public:
    AsmArgImmediate(int);
    ~AsmArgImmediate();

    string Generate();

    bool operator == (int) const;

    bool IsImmediate() const;
};

//-----------------------------------------------------------------------------
class AsmArgRegister: public AsmArg
{
private:
    AsmRegName reg;

protected:
    string GetRegName() const;

public:
    AsmArgRegister(AsmRegName);
    ~AsmArgRegister();

    string Generate();

    bool operator == (AsmArg*) const;

    bool IsRegister() const;
    bool UsesRegister(AsmRegName) const;

    friend class AsmArgIndirect;
};

//-----------------------------------------------------------------------------
class AsmArgIndirect: public AsmArgRegister
{
private:
    int offset;

public:
    AsmArgIndirect(AsmRegName, int shift = 0);
    ~AsmArgIndirect();

    string Generate();

    bool operator == (AsmArg*) const;
    bool operator == (AsmRegName) const;

    bool IsMemoryLocation() const;
    bool UsesRegister(AsmRegName) const;
};

//-----------------------------------------------------------------------------
class AsmArgMemory: public AsmArg
{
private:
    string name;
    bool lvalue;

public:
    AsmArgMemory(const string&, bool lv = false);
    ~AsmArgMemory();

    string Generate();

    bool operator == (AsmArg*) const;

    bool IsMemoryLocation() const;

    bool IsOffset() const;
    void ClearOffset();
};

//-----------------------------------------------------------------------------
class AsmCode
{
private:
    vector <AsmCmd*> cmds;

public:
    AsmCode();
    ~AsmCode();

    void AddCmd(AsmCmd*);
};

//-----------------------------------------------------------------------------
//class Generator
//{
//private:
//    string filename;
//    AsmCode data;
//    AsmCode code;
//
//public:
//    friend class Parser;
//    CodeGenerator(const string& file): filename(file) {}
//    void generate();
//};