.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_9 db "%d", 0
    var_14 db "%d", 0
    var_19 db "%d", 0
    var_24 db "%d", 0
    var_31 db "%d", 0
    var_38 db "%d", 0
    var_43 db "%d", 0
    var_48 db "%d", 0
    var_53 db "%d", 0
    var_60 db "%d", 0
    var_67 db "%d", 0
    var_76 db "%d", 0
    var_85 db "%d", 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 12
    mov eax, 0
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
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
    push dword ptr [ebp + -8]
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
    invoke crt_printf, addr var_9
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_14
    add esp, 4
    mov eax, 0
    push eax
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_19
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
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
    invoke crt_printf, addr var_24
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_31
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_38
    add esp, 4
    push dword ptr [ebp + -12]
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_43
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
    invoke crt_printf, addr var_48
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
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
    invoke crt_printf, addr var_53
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
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
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_60
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -12]
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
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_67
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
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_76
    add esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -12]
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
    invoke crt_printf, addr var_85
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