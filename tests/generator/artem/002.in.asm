.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "1", 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    invoke crt_printf, addr var_0
    add esp, 0
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