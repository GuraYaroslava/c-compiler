.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_1 db "%d", 0

.code
func_one:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    pop eax
    mov dword ptr [ebp + 8], eax
    jmp end_func_one
end_func_one:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    sub esp, 4
    call func_one
    add esp, 0
    invoke crt_printf, addr var_1
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