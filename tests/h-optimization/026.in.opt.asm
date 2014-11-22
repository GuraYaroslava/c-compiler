.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_4 db "bodyIf", 0
    var_6 db "%d", 0dh, 0ah, 0
    var_9 db "%d", 0dh, 0ah, 0
    var_12 db "%d", 0dh, 0ah, 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    sub esp, 0
    sub esp, 0
    sub esp, 0
    mov eax, 3
    push eax
    invoke crt_printf, addr var_6
    add esp, 4
    mov eax, 2
    push eax
    invoke crt_printf, addr var_9
    add esp, 4
    mov eax, 1
    push eax
    invoke crt_printf, addr var_12
    add esp, 4
    mov eax, 0
    push eax
    pop eax
    mov dword ptr [ebp + 8], eax
    jmp end_func_main
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