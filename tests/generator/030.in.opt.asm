.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0dh, 0ah, 0
    var_8 db "%d", 0dh, 0ah, 0
    var_15 db "%d", 0dh, 0ah, 0
    var_20 db "%d", 0dh, 0ah, 0
    var_a dd 1 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    mov eax, 1
    push eax
    push offset var_a
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [var_a + 0]
    push dword ptr [var_a + 0]
    pop ebx
    pop eax
    and eax, ebx
    push eax
    invoke crt_printf, addr var_3
    add esp, 4
    mov eax, 1
    mov ecx, 3
    shl eax, cl
    mov ebx, eax
    push dword ptr [var_a + 0]
    pop eax
    or eax, ebx
    push eax
    invoke crt_printf, addr var_8
    add esp, 4
    push dword ptr [var_a + 0]
    push dword ptr [var_a + 0]
    pop ebx
    pop eax
    xor eax, ebx
    push eax
    invoke crt_printf, addr var_15
    add esp, 4
    push dword ptr [var_a + 0]
    pop eax
    not eax
    push eax
    invoke crt_printf, addr var_20
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