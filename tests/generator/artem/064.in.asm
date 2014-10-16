.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_6 db "%d", 0
    var_11 db "%d", 0
    var_16 db "%d", 0
    var_21 db "%d", 0
    var_26 db "%d", 0
    var_31 db "%d", 0
    var_36 db "%d", 0
    var_41 db "%d", 0
    var_46 db "%d", 0
    var_51 db "%d", 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, 2
    push eax
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
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
    invoke crt_printf, addr var_6
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
    invoke crt_printf, addr var_11
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    invoke crt_printf, addr var_16
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setg al
    push eax
    invoke crt_printf, addr var_21
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setle al
    push eax
    invoke crt_printf, addr var_26
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
    invoke crt_printf, addr var_31
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
    invoke crt_printf, addr var_36
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setge al
    push eax
    invoke crt_printf, addr var_41
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    invoke crt_printf, addr var_46
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setne al
    push eax
    invoke crt_printf, addr var_51
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