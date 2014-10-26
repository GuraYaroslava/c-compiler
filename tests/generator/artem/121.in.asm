.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_1 dd 0.100000
    var_5 dd 0.005000
    var_24 db "%f %f %f", 0
    var_a dd 1 dup(0)
    var_b dd 1 dup(0)
    var_c dd 1 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    push var_1
    pop eax
    push eax
    pop eax
    mov helper4, eax
    fld helper4
    fchs
    fstp helper4
    push helper4
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push var_5
    push offset var_b
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_a + 0]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [var_b + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [var_a + 0]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [var_b + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
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
    push dword ptr [var_b + 0]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [var_a + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    faddp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [var_b + 0]
    pop eax
    mov helper4, eax
    fld helper4
    push dword ptr [var_a + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    fsubp st(1), st
    fstp helper4
    push helper4
    push offset var_c
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_c + 0]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    push dword ptr [var_b + 0]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    push dword ptr [var_a + 0]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_24
    add esp, 24
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