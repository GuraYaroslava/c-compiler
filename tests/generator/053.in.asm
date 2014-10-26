.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_47 db "%d %d", 0dh, 0ah, 0
    var_62 db "%d %d", 0dh, 0ah, 0
    var_78 db "%d %d", 0dh, 0ah, 0
    var_a dd 3 dup(0)
    var_b dd 3 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_distance:
    push ebp
    mov ebp, esp
    sub esp, 0
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
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
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
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
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
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
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
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop ebx
    pop eax
    add eax, ebx
    push eax
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop ebx
    pop eax
    add eax, ebx
    push eax
    pop eax
    mov dword ptr [ebp + 32], eax
    jmp end_func_distance
end_func_distance:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    sub esp, 4
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    call func_distance
    add esp, 24
    sub esp, 4
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_distance
    add esp, 24
    invoke crt_printf, addr var_47
    add esp, 8
    mov eax, 1
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
    sub esp, 4
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_distance
    add esp, 24
    sub esp, 4
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    call func_distance
    add esp, 24
    invoke crt_printf, addr var_62
    add esp, 8
    mov eax, 1
    push eax
    pop eax
    neg eax
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
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    call func_distance
    add esp, 24
    sub esp, 4
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    push dword ptr [var_a + 8]
    push dword ptr [var_a + 4]
    push dword ptr [var_a + 0]
    call func_distance
    add esp, 24
    invoke crt_printf, addr var_78
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