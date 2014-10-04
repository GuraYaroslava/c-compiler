.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0dh, 0ah, 0
    var_8 db "%d", 0dh, 0ah, 0
    var_15 db "%d", 0dh, 0ah, 0
    var_20 db "%d", 0dh, 0ah, 0
    a dd 4 dup(0)

.code
main:
    push ebp
    mov ebp, esp
    push offset a
    mov eax, 1
    push eax
    pop ebx
    pop eax
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [a]
    push dword ptr [a]
    pop ebx
    pop eax
    and eax, ebx
    push eax
    invoke crt_printf, addr var_3
    add esp, 4
    push dword ptr [a]
    mov eax, 1
    push eax
    mov eax, 3
    push eax
    pop ebx
    pop eax
    mov ecx, ebx
    shl eax, cl
    push eax
    pop ebx
    pop eax
    or eax, ebx
    push eax
    invoke crt_printf, addr var_8
    add esp, 4
    push dword ptr [a]
    push dword ptr [a]
    pop ebx
    pop eax
    xor eax, ebx
    push eax
    invoke crt_printf, addr var_15
    add esp, 4
    push dword ptr [a]
    pop eax
    not eax
    push eax
    invoke crt_printf, addr var_20
    add esp, 4
end_main:
    mov esp, ebp
    pop ebp
    ret 0
start:
    sub esp, 4
    call main
    add esp, 4
    ret 0
end start