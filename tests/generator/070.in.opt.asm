.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_27 db "%d %d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_swap:
    push ebp
    mov ebp, esp
    sub esp, 4
    push dword ptr [ebp + 8]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + 12]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    push dword ptr [ebp + 8]
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    push dword ptr [ebp + 12]
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 0
    mov dword ptr [ebp + 16], eax
    jmp end_func_swap
end_func_swap:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, 3
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 3
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 4
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    call func_swap
    add esp, 8
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -4]
    invoke crt_printf, addr var_27
    add esp, 8
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