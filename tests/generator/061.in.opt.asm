.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_19 db "%d", 0
    var_a dd 120600 dup(0)
    var_b dd 1206 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    mov eax, 768
    push eax
    mov eax, 50
    mov ebx, 4824
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push eax
    mov eax, 49
    mov ebx, 48
    imul eax, ebx
    pop ebx
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push eax
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 50
    mov ebx, 4824
    imul eax, ebx
    push offset var_a
    pop ebx
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push eax
    mov eax, 49
    mov ebx, 48
    imul eax, ebx
    pop ebx
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push eax
    mov eax, 0
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_19
    add esp, 4
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