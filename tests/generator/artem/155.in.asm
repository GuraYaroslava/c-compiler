.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%d", 0
    var_2 dd 0.100000
    var_5 db "%d", 0
    var_7 dd 10.000000
    var_8 dd 100.000000
    var_10 db "%d", 0
    var_12 dd 0.000000
    var_17 db "%d", 0
    var_20 dd 1.100000
    var_22 db "%d", 0
    var_24 dd 1.100000
    var_25 dd 1.100000
    var_27 db "%d", 0
    var_29 dd 0.200000
    var_31 dd 10.000000
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    push var_2
    pop eax
    mov helper4, eax
    fld helper4
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
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    seta al
    push eax
    invoke crt_printf, addr var_0
    add esp, 4
    push var_7
    pop eax
    mov helper4, eax
    fld helper4
    push var_8
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
    invoke crt_printf, addr var_5
    add esp, 4
    push var_12
    pop eax
    mov helper4, eax
    fld helper4
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
    fsubp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    mov eax, 0
    push eax
    pop eax
    mov helper4, eax
    fild helper4
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
    invoke crt_printf, addr var_10
    add esp, 4
    mov eax, 0
    push eax
    pop eax
    mov helper4, eax
    fild helper4
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    push var_20
    pop eax
    mov helper4, eax
    fld helper4
    xor eax, eax
    fcompp
    fnstsw ax
    sahf
    mov eax, 0
    setbe al
    push eax
    invoke crt_printf, addr var_17
    add esp, 4
    push var_24
    pop eax
    mov helper4, eax
    fld helper4
    push var_25
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
    invoke crt_printf, addr var_22
    add esp, 4
    push var_29
    pop eax
    mov helper4, eax
    fld helper4
    mov eax, 2
    push eax
    pop eax
    mov helper4, eax
    fild helper4
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    push var_31
    pop eax
    mov helper4, eax
    fld helper4
    fdivp st(1), st
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
    invoke crt_printf, addr var_27
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