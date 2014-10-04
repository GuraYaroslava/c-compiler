.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data

.code
main:
    push ebp
    mov ebp, esp
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