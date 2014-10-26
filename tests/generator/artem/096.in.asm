.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
for_41_start:
for_41_cond:
    pop eax
    cmp eax, 0
    je for_41_end
    jmp for_41_end
for_41_inc:
    jmp for_41_cond
for_41_end:
    mov eax, 1
    push eax
    invoke crt_printf, addr var_0
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