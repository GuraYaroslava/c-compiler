.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_88 db "%d %d %d", 0dh, 0ah, 0
    var_105 db "%d %d %d", 0dh, 0ah, 0
    var_124 db "%d %d %d", 0dh, 0ah, 0
    var_a dd 3 dup(0)
    var_b dd 3 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_add:
    push ebp
    mov ebp, esp
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 16]
    push dword ptr [ebp + 12]
    push dword ptr [ebp + 8]
    pop eax
    mov dword ptr [ebp + 32], eax
    pop eax
    mov dword ptr [ebp + 36], eax
    pop eax
    mov dword ptr [ebp + 40], eax
    jmp end_func_add
end_func_add:
    mov esp, ebp
    pop ebp
    ret 0
func_foo:
    push ebp
    mov ebp, esp
    push dword ptr [ebp + 20]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 20]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 20]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
    mov dword ptr [ecx + 0], edx
    push dword ptr [ebp + 16]
    push dword ptr [ebp + 12]
    push dword ptr [ebp + 8]
    pop eax
    mov dword ptr [ebp + 24], eax
    pop eax
    mov dword ptr [ebp + 28], eax
    pop eax
    mov dword ptr [ebp + 32], eax
    jmp end_func_foo
end_func_foo:
    mov esp, ebp
    pop ebp
    ret 0
func_foo1:
    push ebp
    mov ebp, esp
    sub esp, 12
    push dword ptr [ebp + 20]
    sub esp, 12
    push dword ptr [ebp + 32]
    push dword ptr [ebp + 28]
    push dword ptr [ebp + 24]
    push dword ptr [ebp + 16]
    push dword ptr [ebp + 12]
    push dword ptr [ebp + 8]
    call func_add
    add esp, 24
    call func_foo
    add esp, 16
    sub esp, 12
    push dword ptr [ebp + 32]
    push dword ptr [ebp + 28]
    push dword ptr [ebp + 24]
    push dword ptr [ebp + 16]
    push dword ptr [ebp + 12]
    push dword ptr [ebp + 8]
    call func_add
    add esp, 24
    pop eax
    mov dword ptr [ebp + 36], eax
    pop eax
    mov dword ptr [ebp + 40], eax
    pop eax
    mov dword ptr [ebp + 44], eax
    jmp end_func_foo1
end_func_foo1:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 12
    mov eax, 1
    push eax
    push offset var_a
    pop eax
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    push eax
    push offset var_a
    pop eax
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 3
    push eax
    push offset var_a
    pop eax
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    neg eax
    push eax
    push offset var_b
    pop eax
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    neg eax
    push eax
    push offset var_b
    pop eax
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 3
    neg eax
    push eax
    push offset var_b
    pop eax
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 12
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_add
    add esp, 24
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_88
    add esp, 12
    sub esp, 12
    mov eax, 3
    push eax
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_foo
    add esp, 16
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_105
    add esp, 12
    sub esp, 12
    mov eax, 1
    neg eax
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push eax
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_foo1
    add esp, 28
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_124
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