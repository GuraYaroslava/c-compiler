.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_2 db "%d", 0

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
func_two:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 2
    push eax
    pop eax
    mov dword ptr [ebp + 8], eax
    jmp end_func_two
end_func_two:
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
    sub esp, 4
    call func_two
    add esp, 0
    pop ebx
    pop eax
    add eax, ebx
    push eax
    invoke crt_printf, addr var_2
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