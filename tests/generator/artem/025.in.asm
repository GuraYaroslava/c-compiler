.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_12 db "%d", 0
    var_a dd 10 dup(0)

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    push offset var_a
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_a
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_12
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