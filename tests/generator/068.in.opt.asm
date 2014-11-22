.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_41 db "(%d, %d) -> (%d, %d)", 0dh, 0ah, 0
    var_63 db "(%d, %d) -> (%d, %d)", 0dh, 0ah, 0
    var_global dd 4 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 24
    push offset var_global
    mov eax, ebp
    mov ebx, -20
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    neg eax
    push eax
    push offset var_global
    pop eax
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    push eax
    push offset var_global
    pop eax
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    push eax
    push offset var_global
    pop eax
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    neg eax
    push eax
    push offset var_global
    pop eax
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_global + 12]
    push dword ptr [var_global + 8]
    push dword ptr [var_global + 4]
    push dword ptr [var_global + 0]
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    pop ebx
    mov dword ptr [eax + 12], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -20]
    pop eax
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -20]
    pop eax
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -20]
    pop eax
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -20]
    pop eax
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_41
    add esp, 16
    push dword ptr [ebp + -24]
    pop eax
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -24]
    pop eax
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -24]
    pop eax
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    push dword ptr [ebp + -24]
    pop eax
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_63
    add esp, 16
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