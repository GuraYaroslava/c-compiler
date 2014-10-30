#include "asm_optimizer.h"

static bool IsMemory(AsmArg* arg)
{
    return dynamic_cast<AsmArgMemory*>(arg)
        || dynamic_cast<AsmArgIndirect*>(arg)
        || dynamic_cast<AsmArgLabel*>(arg)
        || dynamic_cast<AsmArgFloat*>(arg)
        || dynamic_cast<AsmArgString*>(arg);
}

static bool UsesStack(AsmCmd* cmd)
{
    if (AsmCmd2* binaryOpCode = dynamic_cast<AsmCmd2*>(cmd))
    {
        return *binaryOpCode->GetFirst() == EBP || *binaryOpCode->GetFirst() == ESP
            || *binaryOpCode->GetSecond() == EBP || *binaryOpCode->GetSecond() == ESP;
    }
    else if (AsmCmd1* unaryOpCode = dynamic_cast<AsmCmd1*>(cmd))
    {
        return *unaryOpCode == cmdPOP || *unaryOpCode == cmdPUSH
            || *unaryOpCode == cmdCALL || *unaryOpCode == cmdRET;
    }
    else if (dynamic_cast<AsmCmdPrint*>(cmd))
    {
        return true;
    }
    return false;
}

static bool IsArgument(AsmArg* arg, AsmCmd* cmd)
{
    if (AsmCmd2* binaryOpCode = dynamic_cast<AsmCmd2*>(cmd))
    {
        AsmArgIndirect* ind = dynamic_cast<AsmArgIndirect*>(arg);
        AsmArgIndirect* ind1 = dynamic_cast<AsmArgIndirect*>(binaryOpCode->GetFirst());
        AsmArgIndirect* ind2 = dynamic_cast<AsmArgIndirect*>(binaryOpCode->GetSecond());
        return ind && ind->usesRegister(binaryOpCode->GetFirst()) || ind && ind->usesRegister(binaryOpCode->GetSecond())
            || ind1 && ind1->usesRegister(arg) || ind2 && ind2->usesRegister(arg)
            || *binaryOpCode->GetFirst() == arg || *binaryOpCode->GetSecond() == arg;
    }
    else if (AsmCmd1* unaryOpCode = dynamic_cast<AsmCmd1*>(cmd))
    {
        AsmArgIndirect* ind = dynamic_cast<AsmArgIndirect*>(arg);
        AsmArgIndirect* ind1 = dynamic_cast<AsmArgIndirect*>(unaryOpCode->GetArgument());
        return ind && ind->usesRegister(unaryOpCode->GetArgument())
            || ind1 && ind1->usesRegister(arg)
            || *unaryOpCode->GetArgument() == arg
            || *arg == ESP || *arg == EBP;
    }
    return false;
}

//-----------------------------------------------------------------------------
bool AsmOptimization::Optimize(AsmCode& code)
{
    bool res = false;
    for (int i = 0; i < code.Size(); ++i)
    {
        res = Optimize(code, i) || res;
    }

    return res;
}

bool AsmOptimization::Optimize(AsmCode&, int)
{
    return false;
}

//-----------------------------------------------------------------------------
//for example
//push eax
//pop eax

bool PushPopOptimization::Optimize(AsmCode& code, int index)
{
    if (index + 1 == code.Size())
    {
        return false;
    }

    AsmCmd1* cmd1 = dynamic_cast<AsmCmd1*>(code[index]);
    AsmCmd1* cmd2 = dynamic_cast<AsmCmd1*>(code[index + 1]);

    if (cmd1 && cmd2 && *cmd1 == cmdPUSH  && *cmd2 == cmdPOP)
    {
        if (*cmd1->GetArgument() == cmd2->GetArgument())
        {
            code.Delete(index, index + 1);
            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
//for example
//push 12                  ; output:
//pop eax                  ; mov eax, 12
//
//push dword ptr [ebp + -4]; output:
//pop eax                  ; mov eax, dword ptr [ebp + -4]

bool PushPopToMovOptimization::Optimize(AsmCode& code, int index)
{
    if (index + 1 == code.Size())
    {
        return false;
    }

    AsmCmd1* cmd1 = dynamic_cast<AsmCmd1*>(code[index]);
    AsmCmd1* cmd2 = dynamic_cast<AsmCmd1*>(code[index + 1]);

    if (cmd1 && cmd2 && *cmd1 == cmdPUSH  && *cmd2 == cmdPOP)
    {
        if (*cmd1->GetArgument() != cmd2->GetArgument())
        {
            if (IsMemory(cmd1->GetArgument()) && IsMemory(cmd2->GetArgument()))
            {
                return false;
            }
            AsmCmd2* optCmd = new AsmCmd2(cmdMOV, cmd2->GetArgument(), cmd1->GetArgument());
            code.Delete(index, index + 1);
            code.Insert(optCmd, index);
            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
//for example
//mov eax, 12      ; output:
//mov ebx, eax     ; mov ebx, 12

bool MovChainOptimization::Optimize(AsmCode& code, int index)
{
    if (index + 1 == code.Size())
    {
        return false;
    }

    AsmCmd2* cmd1 = dynamic_cast<AsmCmd2*>(code[index]);
    AsmCmd2* cmd2 = dynamic_cast<AsmCmd2*>(code[index + 1]);

    if (cmd1 && cmd2
        && *cmd1 == cmdMOV && *cmd2 == cmdMOV
        && *cmd1->GetFirst() != EBP && *cmd1->GetSecond() != ESP
        && *cmd2->GetSecond() == cmd1->GetFirst()
        && !IsMemory(cmd1->GetSecond()) && !IsMemory(cmd2->GetFirst()))
    {
        AsmCmd2* optCmd = new AsmCmd2(cmdMOV, cmd2->GetFirst(), cmd1->GetSecond());
        code.Delete(index, index + 1);
        code.Insert(optCmd, index);
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
bool AddSubZero::Optimize(AsmCode& code, int index)
{
    if (index == code.Size())
    {
        return false;
    }

    AsmCmd2* cmd = dynamic_cast<AsmCmd2*>(code[index]);
    if (cmd && (*cmd == cmdSUB || *cmd == cmdADD) && *cmd->GetSecond() == "0")
    {
        code.Delete(index);
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
//for example
//_____input____;_____PopToUpPushToDown____;____PushPopOptimization____;
//mov eax, 1    ;mov eax, 1                ;mov eax, 1                 ;
//push eax      ;mov ebx, 1                ;mov ebx, 1                 ;
//mov ebx, 1    ;push eax                  ;add eax, ebx               ;
//pop eax       ;pop eax                   ;                           ;
//add eax, ebx  ;add eax, ebx              ;                           ;

bool PopToUpPushToDown::Optimize(AsmCode& code)
{
    bool res = false;
    for (int i = 0; i < code.Size(); ++i)
    {
        AsmCmd1* cmd = dynamic_cast<AsmCmd1*>(code[i]);
        if (cmd && *cmd == cmdPUSH)
        {
            res = Action(code, cmd, i, 1) || res;
        }
        else if (cmd && *cmd == cmdPOP)
        {
            res = Action(code, cmd, i, -1) || res;
        }
    }
    return res;
}

bool PopToUpPushToDown::Action(AsmCode& code, AsmCmd1* cmd, int i, int inc)
{
    int j = i;
    while (0 < j && j + 1 < code.Size()
        && !UsesStack(code[j + inc])
        && !IsArgument(cmd->GetArgument(), code[j + inc]))
    {
        j += inc;
    }
    code.Move(i, j);
    return j != i;
}

//-----------------------------------------------------------------------------
AsmOptimizer::AsmOptimizer()
{
    optimizations.push_back(new PushPopOptimization());
    optimizations.push_back(new PushPopToMovOptimization());
    optimizations.push_back(new MovChainOptimization());
    optimizations.push_back(new AddSubZero());
    optimizations.push_back(new PopToUpPushToDown());
}

AsmOptimizer::~AsmOptimizer() {}

void AsmOptimizer::Optimize(AsmCode& code)
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (auto opt = optimizations.begin(); opt != optimizations.end(); ++opt)
        {
            flag = ((*opt)->Optimize(code)) || flag;
        }
    }
}
