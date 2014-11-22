.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_19 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_Add:
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
    jmp end_func_Add
end_func_Add:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 4
    mov eax, 5
    push eax
    push dword ptr [ebp + -4]
    call func_Add
    add esp, 8
    invoke crt_printf, addr var_19
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