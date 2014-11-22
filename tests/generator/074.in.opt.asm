.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_8 dd 3.000000
    var_42 dd 2.300000
    var_53 db "%f %f %f", 0
    var_b dd 3 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 16
    mov eax, 3
    mov helper4, eax
    fild helper4
    fstp helper4
    push helper4
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push var_8
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov helper4, eax
    fld helper4
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fdivp st(1), st
    fstp helper4
    push helper4
    pop eax
    mov helper4, eax
    fld helper4
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fmulp st(1), st
    fstp helper4
    push helper4
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -16]
    pop eax
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov helper4, eax
    fld helper4
    push var_42
    pop eax
    mov helper4, eax
    fld helper4
    fdivp st(1), st
    fstp helper4
    push helper4
    push dword ptr [ebp + -16]
    pop eax
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov helper4, eax
    fld helper4
    fchs
    fstp helper4
    push helper4
    push dword ptr [ebp + -16]
    pop eax
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    pop eax
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    push offset var_b
    pop eax
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    push offset var_b
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    pop helper4
    fld helper4
    fstp helper8
    mov eax, offset helper8
    push dword ptr [eax + 4]
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_53
    add esp, 24
    mov eax, 0
    mov dword ptr [ebp + 8], eax
    jmp end_func_main
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