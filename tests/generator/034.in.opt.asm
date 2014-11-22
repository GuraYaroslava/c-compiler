.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_32 db "%d %d", 0
    var_a dd 2 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    mov eax, 3
    push eax
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    cdq
    idiv ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 4
    add eax, ebx
    mov ebx, 3
    push dword ptr [eax + 0]
    pop eax
    cdq
    imul ebx
    mov ebx, 1
    sub eax, ebx
    mov ebx, eax
    pop eax
    cdq
    imul ebx
    mov ebx, eax
    pop eax
    add eax, ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    sub eax, ebx
    mov dword ptr [ecx + 0], eax
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
    invoke crt_printf, addr var_32
    add esp, 8
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