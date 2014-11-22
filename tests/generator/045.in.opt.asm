.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_17 db "%d %d %d", 0
    var_a dd 3 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 12
    mov eax, 30
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
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
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    mov eax, ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    push offset var_a
    pop eax
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_17
    add esp, 12
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