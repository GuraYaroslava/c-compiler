.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0
    a dd 4 dup(0)

.code
main:
    push ebp
    mov ebp, esp
    push offset a
    mov eax, 12
    push eax
    pop ebx
    pop eax
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [a]
    invoke crt_printf, addr var_3
    add esp, 4
    mov eax, 0
    push eax
    pop eax
    mov dword ptr [ebp + 8], eax
    jmp end_main
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