.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0
    var_8 db "%d", 0
    var_13 db "%d", 0
    var_18 db "%d", 0
    var_23 db "%d", 0
    var_28 db "%d", 0
    var_33 db "%d", 0
    var_38 db "%d", 0
    var_43 db "%d", 0
    var_48 db "%d", 0

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
    mov eax, 1
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    invoke crt_printf, addr var_3
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 1
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_8
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 2
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    invoke crt_printf, addr var_13
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 2
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setg al
    push eax
    invoke crt_printf, addr var_18
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 2
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setle al
    push eax
    invoke crt_printf, addr var_23
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 1
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setle al
    push eax
    invoke crt_printf, addr var_28
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 1
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setge al
    push eax
    invoke crt_printf, addr var_33
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 2
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setge al
    push eax
    invoke crt_printf, addr var_38
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 3
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    invoke crt_printf, addr var_43
    add esp, 4
    push dword ptr [ebp + -4]
    mov eax, 3
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_48
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