.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0

.code
kvadrat:
    push ebp
    mov ebp, esp
    push dword ptr [ebp + 8]
    push dword ptr [ebp + 8]
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop eax
    mov dword ptr [ebp + 12], eax
    jmp end_kvadrat
end_kvadrat:
    mov esp, ebp
    pop ebp
    ret 0
main:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 3
    push eax
    call kvadrat
    add esp, 4
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