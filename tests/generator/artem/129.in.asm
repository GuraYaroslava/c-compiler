.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%f", 0
    var_a dd 1 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    push dword ptr [var_a + 0]
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