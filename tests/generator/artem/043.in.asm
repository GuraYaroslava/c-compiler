.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_12 db "%d", 0dh, 0ah, 0
    var_15 db "%d", 0dh, 0ah, 0
    var_18 db "%d", 0dh, 0ah, 0
    var_21 db "%d", 0dh, 0ah, 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 0
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
    sub esp, 4
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
    mov eax, 2
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 4
    mov eax, 3
    push eax
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -16]
    invoke crt_printf, addr var_12
    add esp, 4
    push dword ptr [ebp + -12]
    invoke crt_printf, addr var_15
    add esp, 4
    push dword ptr [ebp + -8]
    invoke crt_printf, addr var_18
    add esp, 4
    push dword ptr [ebp + -4]
    invoke crt_printf, addr var_21
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