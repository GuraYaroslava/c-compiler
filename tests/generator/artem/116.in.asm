.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%f", 0
    var_2 dd 0.001000
    var_4 dd 0.100000
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    push var_2
    pop eax
    push eax
    pop eax
    mov helper4, eax
    fld helper4
    fchs
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    push var_4
    pop eax
    push eax
    pop eax
    mov helper4, eax
    fld helper4
    fchs
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_0
    add esp, 8
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