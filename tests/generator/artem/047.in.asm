.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_3 db "%d", 0

.code
func_sigma:
    push ebp
    mov ebp, esp
    sub esp, 0
    push dword ptr [ebp + 8]
    push dword ptr [ebp + 12]
    pop ebx
    pop eax
    add eax, ebx
    push eax
    pop eax
    mov dword ptr [ebp + 16], eax
    jmp end_func_sigma
end_func_sigma:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    sub esp, 4
    mov eax, 1
    push eax
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    call func_sigma
    add esp, 8
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