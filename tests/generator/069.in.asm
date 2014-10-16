.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_7 db "%d", 0dh, 0ah, 0
    var_14 db "%d", 0dh, 0ah, 0
    var_22 db "%d", 0dh, 0ah, 0
    var_28 db "%d", 0dh, 0ah, 0
    var_35 db "%d", 0dh, 0ah, 0
    var_44 db "%d", 0dh, 0ah, 0
    var_54 db "%d", 0dh, 0ah, 0

.code
func_loop:
    push ebp
    mov ebp, esp
    sub esp, 0
    push dword ptr [ebp + 8]
    pop eax
    mov dword ptr [ebp + 12], eax
    jmp end_func_loop
end_func_loop:
    mov esp, ebp
    pop ebp
    ret 0
func_equal:
    push ebp
    mov ebp, esp
    sub esp, 0
    push dword ptr [ebp + 8]
    push dword ptr [ebp + 12]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    pop eax
    mov dword ptr [ebp + 16], eax
    jmp end_func_equal
end_func_equal:
    mov esp, ebp
    pop ebp
    ret 0
func_inc:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    pop eax
    mov dword ptr [ebp + 12], eax
    jmp end_func_inc
end_func_inc:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    sub esp, 4
    mov eax, 1
    push eax
    call func_loop
    add esp, 4
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    invoke crt_printf, addr var_7
    add esp, 4
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    sub esp, 4
    mov eax, 10
    push eax
    call func_loop
    add esp, 4
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    invoke crt_printf, addr var_14
    add esp, 4
    sub esp, 4
    mov eax, 1
    push eax
    mov eax, 1
    push eax
    call func_equal
    add esp, 8
    invoke crt_printf, addr var_22
    add esp, 4
    sub esp, 4
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    mov eax, 1
    push eax
    call func_equal
    add esp, 8
    invoke crt_printf, addr var_28
    add esp, 4
    sub esp, 4
    sub esp, 4
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    call func_inc
    add esp, 4
    mov eax, 0
    push eax
    call func_equal
    add esp, 8
    invoke crt_printf, addr var_35
    add esp, 4
    sub esp, 4
    sub esp, 4
    mov eax, 1
    push eax
    call func_loop
    add esp, 4
    sub esp, 4
    mov eax, 1
    push eax
    call func_loop
    add esp, 4
    call func_equal
    add esp, 8
    invoke crt_printf, addr var_44
    add esp, 4
    sub esp, 4
    mov eax, 1
    push eax
    sub esp, 4
    sub esp, 4
    mov eax, 0
    push eax
    call func_loop
    add esp, 4
    call func_inc
    add esp, 4
    call func_equal
    add esp, 8
    invoke crt_printf, addr var_54
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