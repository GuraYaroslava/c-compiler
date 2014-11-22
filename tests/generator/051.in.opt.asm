.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_43 db "%d %d %d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_add:
    push ebp
    mov ebp, esp
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 16]
    push dword ptr [ebp + 12]
    push dword ptr [ebp + 8]
    pop eax
    mov dword ptr [ebp + 32], eax
    pop eax
    mov dword ptr [ebp + 36], eax
    pop eax
    mov dword ptr [ebp + 40], eax
    jmp end_func_add
end_func_add:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 24
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 3
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 12
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    call func_add
    add esp, 24
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_43
    add esp, 12
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