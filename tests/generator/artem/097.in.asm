.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_1 db "%d", 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
while_41_start:
while_41_cond:
    mov eax, 1
    push eax
    pop eax
    cmp eax, 0
    je while_41_end
    jmp while_41_end
    jmp while_41_cond
while_41_end:
    mov eax, 1
    push eax
    invoke crt_printf, addr var_1
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