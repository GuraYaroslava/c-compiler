.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_1 dd 3.000000
    var_6 db "%f %f", 0dh, 0ah, 0
    var_18 db "%f %f", 0dh, 0ah, 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, dword ptr [ebp + -4]
    mov helper4, eax
    fld helper4
    push var_1
    pop eax
    mov helper4, eax
    fld helper4
    faddp st(1), st
    fstp helper4
    push helper4
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    push ebx
    mov eax, dword ptr [ebp + -8]
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
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    push ebx
    push dword ptr [ebp + -8]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    push dword ptr [ebp + -4]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_6
    add esp, 16
    mov eax, dword ptr [ebp + -4]
    mov helper4, eax
    fld helper4
    push dword ptr [ebp + -8]
    pop eax
    mov helper4, eax
    fld helper4
    fdivp st(1), st
    fstp helper4
    push helper4
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    push ebx
    mov eax, dword ptr [ebp + -8]
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
    push ebx
    push dword ptr [ebp + -8]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    push dword ptr [ebp + -4]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_18
    add esp, 16
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