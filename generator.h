#pragma once

#include <vector>
#include "token.h"
using namespace std;

class AsmArgString;
AsmArgString* GenAsmString(const string&);

typedef enum
{
    cmdDD,
    cmdDB,
    cmdDQ,

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

string AsmCmdNameToString(AsmCmdName);

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
    ST0,
    ST1
} AsmRegName;

//-----------------------------------------------------------------------------
class AsmCmd
{
public:
    virtual string Generate();
};

//-----------------------------------------------------------------------------
class AsmCode;

class AsmCmd0: public AsmCmd
{
protected:
    AsmCmdName opcode;

public:
    AsmCmd0(AsmCmdName);
    ~AsmCmd0();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmArg;

class AsmCmd1: public AsmCmd0, public AsmCmd
{
private:
    AsmArg* arg;

public:
    AsmCmd1(AsmCmdName, AsmArg*);
    ~AsmCmd1();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmCmd2: public AsmCmd0, public AsmCmd
{
private:
    AsmArg *arg1, *arg2;

public:
    AsmCmd2(AsmCmdName, AsmArg*, AsmArg*);
    ~AsmCmd2();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmRowCmd: public AsmCmd
{
private:
    string str;
public:
    AsmRowCmd(string);
    ~AsmRowCmd();
};

//-----------------------------------------------------------------------------
class AsmArgRegister;

class AsmArg
{
public:
    AsmArg();
    ~AsmArg();

    virtual string Generate();

    virtual bool operator == (int) const;
    virtual bool operator == (AsmArg*) const;
    virtual bool operator == (AsmRegName) const;

    bool operator != (AsmArg*) const;
    bool operator != (AsmRegName) const;
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
};

//-----------------------------------------------------------------------------
class AsmArgRegister: public AsmArg
{
private:
    AsmRegName reg;

protected:
    string RegNameToString() const;

public:
    AsmArgRegister(AsmRegName);
    ~AsmArgRegister();

    string Generate();

    bool operator == (AsmArg*) const;

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
};

//-----------------------------------------------------------------------------
class AsmArgDup: public AsmArg
{
private:
    int size;

public:
    AsmArgDup(int);
    ~AsmArgDup();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmArgLabel: public AsmArg
{
private:
    string name;

public:
    AsmArgLabel(string);
    ~AsmArgLabel();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmLabel: public AsmCmd
{
private:
    AsmArgLabel* label;

public:
    friend class AsmCode;

    AsmLabel(string);
    AsmLabel(AsmArgLabel*);
    ~AsmLabel();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmArgString: public AsmArg
{
private:
    string val;

public:
    AsmArgString(string);
    ~AsmArgString();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmArgFloat: public AsmArg
{
private:
    float val;

public:
    AsmArgFloat(float);
    ~AsmArgFloat();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmArgInt: public AsmArg
{
private:
    int val;

public:
    AsmArgInt(int);
    ~AsmArgInt();

   string Generate();
};

//-----------------------------------------------------------------------------
class AsmCmdPrint: public AsmCmd0
{
private:
    AsmArgMemory* format;

public:
    AsmCmdPrint(AsmArgMemory*);
    ~AsmCmdPrint();

    string Generate();
};

//-----------------------------------------------------------------------------
class AsmCode
{
private:
    vector <AsmCmd*> cmds;

public:
    friend class Generator;

    AsmCode();
    ~AsmCode();

    void AddCmd(string);

    void AddCmd(AsmCmd*);

    //cmd
    void AddCmd(AsmCmdName);

    //cmd arg
    void AddCmd(AsmCmdName, AsmArg*);

    //cmd arg1, arg2
    void AddCmd(AsmCmdName, AsmArg*, AsmArg*);

    //invoke crt_printf addr format
    void AddCmd(AsmArgMemory*);

    //cmd label
    void AddCmd(AsmCmdName, AsmLabel*);

    //label:
    void AddCmd(AsmLabel*);

    //for example, mov eax, 12345
    void AddCmd(AsmCmdName, AsmRegName, int);

    //cmd register
    void AddCmd(AsmCmdName, AsmRegName);

    //cmd register, register
    void AddCmd(AsmCmdName, AsmRegName, AsmRegName);

    //end label:
    void AddCmd(AsmArgLabel*);

    void AddCmd(AsmCmdName, AsmRegName, AsmArg*);
    void AddCmd(AsmCmdName, AsmArg*, AsmRegName);
};

//-----------------------------------------------------------------------------
class Generator
{
private:
    string filename;
    AsmCode data;
    AsmCode code;

public:
    friend class Parser;

    Generator(const string&);
    ~Generator();

    void Generate();
};