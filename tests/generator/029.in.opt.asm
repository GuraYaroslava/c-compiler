.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_30 db "%d %d %d", 0
    var_a dd 10 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    mov eax, 15
    push eax
    mov eax, 2
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 10
    push eax
    mov eax, 1
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    mov eax, 1
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    mov eax, 2
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, 1
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_30
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