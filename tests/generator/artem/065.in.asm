.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%d", 0
    var_5 db "%d", 0
    var_10 db "%d", 0
    var_15 db "%d", 0
    var_22 db "%d", 0
    var_29 db "%d", 0
    var_34 db "%d", 0
    var_39 db "%d", 0
    var_44 db "%d", 0
    var_51 db "%d", 0
    var_58 db "%d", 0
    var_67 db "%d", 0
    var_76 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    mov eax, 2
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_0
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_5
    add esp, 4
    mov eax, 0
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_10
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 2
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 3
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_15
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 3
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_22
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_29
    add esp, 4
    mov eax, 0
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_34
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 1
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_39
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 2
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 3
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_44
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 2
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_51
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 0
    push eax
    mov eax, 1
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_58
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 1
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 0
    push eax
    mov eax, 1
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_67
    add esp, 4
    mov eax, 1
    push eax
    mov eax, 0
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    mov eax, 0
    push eax
    mov eax, 1
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    imul eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_76
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