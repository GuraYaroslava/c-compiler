.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "Hello, World!", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_sayHi:
    push ebp
    mov ebp, esp
    invoke crt_printf, addr var_0
    mov eax, 0
    mov dword ptr [ebp + 8], eax
    jmp end_func_sayHi
end_func_sayHi:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 4
    call func_sayHi
    mov eax, 0
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