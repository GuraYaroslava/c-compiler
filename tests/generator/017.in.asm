.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%d", 0

.code
main:
    push ebp
    mov ebp, esp
    mov eax, 5
    push eax
    mov eax, 3
    push eax
    pop ebx
    pop eax
    cdq
    idiv ebx
    mov eax, edx
    push eax
    invoke crt_printf, addr var_0
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