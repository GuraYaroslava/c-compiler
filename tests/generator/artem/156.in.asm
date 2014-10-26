.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_1 dd 0.300000
    var_5 dd 0.001000
    var_8 db "%d", 0
    var_13 db "%d", 0
    var_18 db "%d", 0
    var_22 dd 1000.000000
    var_25 db "%d", 0
    var_30 db "%d", 0
    var_32 dd 0.090000
    var_37 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 8
    push var_1
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    push var_5
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -8]
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    seta al
    push eax
    invoke crt_printf, addr var_8
    add esp, 4
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -8]
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    setb al
    push eax
    invoke crt_printf, addr var_13
    add esp, 4
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -8]
    pop eax
    mov helper4, eax
    fld helper4
    push var_22
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    sete al
    push eax
    invoke crt_printf, addr var_18
    add esp, 4
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -8]
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_25
    add esp, 4
    push var_32
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -4]
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    setae al
    push eax
    invoke crt_printf, addr var_30
    add esp, 4
    mov eax, 1
    push eax
    pop eax
    mov helper4, eax
    fild helper4
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -8]
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    setb al
    push eax
    invoke crt_printf, addr var_37
    add esp, 4
end_func_main:
    mov esp, ebp
    pop ebp
    ret 0
start:
    sub esp, 4
    call func_main
    add esp, 4
    ret 0
end start