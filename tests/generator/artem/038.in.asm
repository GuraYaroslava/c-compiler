.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_22 db "%d %d %d", 0
    var_a dd 1 dup(0)
    var_b dd 10 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    push offset var_b
    mov eax, 0
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    push eax
    push offset var_b
    mov eax, 1
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 3
    push eax
    push offset var_b
    mov eax, 2
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    mov eax, 1
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_a + 0]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    push dword ptr [var_a + 0]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    push dword ptr [var_a + 0]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    invoke crt_printf, addr var_22
    add esp, 12
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