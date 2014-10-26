.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_kvadrat:
    push ebp
    mov ebp, esp
    sub esp, 0
    push dword ptr [ebp + 8]
    push dword ptr [ebp + 8]
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop eax
    mov dword ptr [ebp + 12], eax
    jmp end_func_kvadrat
end_func_kvadrat:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    sub esp, 4
    mov eax, 3
    push eax
    call func_kvadrat
    add esp, 4
    invoke crt_printf, addr var_3
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