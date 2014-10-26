.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_27 db "%d %d", 0
    var_a dd 100 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 5
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 15
    push eax
    pop eax
    neg eax
    push eax
    push offset var_a
    push dword ptr [ebp + -4]
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
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -4]
    mov eax, 5
    push eax
    pop ebx
    pop eax
    cdq
    idiv ebx
    push eax
    mov eax, 3
    push eax
    pop ebx
    pop eax
    cdq
    idiv ebx
    push edx
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    mov eax, 1
    push eax
    pop ebx
    pop eax
    cdq
    idiv ebx
    push eax
    mov eax, 1
    push eax
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push offset var_a
    mov eax, 99
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_27
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