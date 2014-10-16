.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_9 db "%d", 0dh, 0ah, 0
    var_17 db "%d", 0dh, 0ah, 0
    var_26 db "%d", 0dh, 0ah, 0
    var_32 db "%d", 0dh, 0ah, 0
    var_42 db "%d", 0dh, 0ah, 0
    var_48 db "%d", 0dh, 0ah, 0
    var_51 db "%d", 0dh, 0ah, 0
    var_55 db "%d", 0dh, 0ah, 0
    var_a dd 1 dup(0)
    var_b dd 1 dup(0)

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 0
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
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
    invoke crt_printf, addr var_9
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
    invoke crt_printf, addr var_17
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
    invoke crt_printf, addr var_26
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
    invoke crt_printf, addr var_32
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
    invoke crt_printf, addr var_42
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
    invoke crt_printf, addr var_48
    add esp, 4
    push dword ptr [var_a + 0]
    pop eax
    neg eax
    push eax
    invoke crt_printf, addr var_51
    add esp, 4
    push dword ptr [var_a + 0]
    pop eax
    push eax
    invoke crt_printf, addr var_55
    add esp, 4
    mov eax, 0
    push eax
    pop eax
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