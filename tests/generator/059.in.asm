.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "(%d, %d)", 0dh, 0ah, 0
    var_a dd 2 dup(0)
    var_b dd 2 dup(0)

.code
func_print:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_0
    add esp, 8
    mov eax, 0
    push eax
    pop eax
    mov dword ptr [ebp + 16], eax
    jmp end_func_print
end_func_print:
    mov esp, ebp
    pop ebp
    ret 0
func_swap:
    push ebp
    mov ebp, esp
    sub esp, 8
    push dword ptr [ebp + 8]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 4]
    push eax
    mov eax, dword ptr [ebx + 0]
    push eax
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + 12]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 4]
    push eax
    mov eax, dword ptr [ebx + 0]
    push eax
    push dword ptr [ebp + 8]
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + 12]
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    mov eax, ebx
    push eax
    mov eax, 0
    push eax
    pop eax
    mov dword ptr [ebp + 16], eax
    jmp end_func_swap
end_func_swap:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 0
    push eax
    push offset var_a
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 5
    push eax
    push offset var_b
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 4
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_print
    add esp, 8
    sub esp, 4
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    call func_print
    add esp, 8
    sub esp, 4
    push offset var_b
    push offset var_a
    call func_swap
    add esp, 8
    sub esp, 4
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_print
    add esp, 8
    sub esp, 4
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    call func_print
    add esp, 8
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