.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0
    var_8 db "%d", 0
    var_13 db "%d", 0
    var_18 db "%d", 0
    var_25 db "%d", 0
    var_32 db "%d", 0
    var_37 db "%d", 0
    var_42 db "%d", 0
    var_47 db "%d", 0
    var_54 db "%d", 0
    var_61 db "%d", 0
    var_70 db "%d", 0
    var_79 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 1
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
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_3
    add esp, 4
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_8
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
    invoke crt_printf, addr var_13
    add esp, 4
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_18
    add esp, 4
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_25
    add esp, 4
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_32
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
    invoke crt_printf, addr var_37
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_42
    add esp, 4
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_47
    add esp, 4
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_54
    add esp, 4
    push dword ptr [ebp + -4]
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
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_61
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -4]
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
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_70
    add esp, 4
    push dword ptr [ebp + -4]
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
    push dword ptr [ebp + -4]
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
    invoke crt_printf, addr var_79
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