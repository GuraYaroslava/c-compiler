.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_6 db "%d", 0dh, 0ah, 0
    var_14 db "%d", 0dh, 0ah, 0
    var_23 db "%d", 0dh, 0ah, 0
    var_29 db "%d", 0dh, 0ah, 0
    var_39 db "%d", 0dh, 0ah, 0
    var_45 db "%d", 0dh, 0ah, 0
    var_a dd 1 dup(0)
    var_b dd 1 dup(0)

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 3
    push eax
    push offset var_b
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_b + 0]
    push offset var_a
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [var_a + 0]
    invoke crt_printf, addr var_6
    add esp, 4
    mov eax, 3
    push eax
    push dword ptr [var_b + 0]
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    sub eax, ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [var_a + 0]
    invoke crt_printf, addr var_14
    add esp, 4
    mov eax, 1
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 15
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [var_a + 0]
    invoke crt_printf, addr var_23
    add esp, 4
    mov eax, 3
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [var_a + 0]
    invoke crt_printf, addr var_29
    add esp, 4
    push dword ptr [var_b + 0]
    mov eax, 3
    push eax
    mov eax, 3
    push eax
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
    push offset var_a
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [var_a + 0]
    invoke crt_printf, addr var_39
    add esp, 4
    mov eax, 2
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
    mov dword ptr [ecx + 0], edx
    push dword ptr [var_a + 0]
    invoke crt_printf, addr var_45
    add esp, 4
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