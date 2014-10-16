.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%d", 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    mov eax, 1
    push eax
    pop eax
    pop ebx
    cmp eax, 0
    mov eax, 0
    setne al
    cmp ebx, 0
    mov ebx, 0
    setne bl
    add eax, ebx
    cmp eax, 0
    mov eax, 0
    setne al
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