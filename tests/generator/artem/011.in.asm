.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0dh, 0ah, 0
    var_8 db "%d", 0dh, 0ah, 0
    var_a dd 1 dup(0)

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_a + 0]
    mov eax, 3
    push eax
    pop ebx
    pop eax
    mov ecx, ebx
    shl eax, cl
    push eax
    invoke crt_printf, addr var_3
    add esp, 4
    push dword ptr [var_a + 0]
    mov eax, 2
    push eax
    pop ebx
    pop eax
    mov ecx, ebx
    shr eax, cl
    push eax
    invoke crt_printf, addr var_8
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