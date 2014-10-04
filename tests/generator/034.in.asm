.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_32 db "%d %d", 0
    a dd 0 dup(0)

.code
main:
    push ebp
    mov ebp, esp
    push offset a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    mov eax, 3
    push eax
    pop ebx
    pop eax
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset a
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    push offset a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    push offset a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    pop ebx
    pop eax
    cdq
    idiv ebx
    push eax
    push offset a
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, 3
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    mov eax, 1
    push eax
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop ebx
    pop eax
    add eax, ebx
    push eax
    pop ebx
    pop eax
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    sub eax, ebx
    mov dword ptr [ecx + 0], eax
    push offset a
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset a
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_32
    add esp, 8
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