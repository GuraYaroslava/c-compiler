.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_47 db "(%d, %d)", 0dh, 0ah, 0
    var_p dd 20 dup(0)
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 44
    mov eax, 0
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 0
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
for_41_start:
for_41_cond:
    mov ebx, 10
    push eax
    push dword ptr [ebp + -4]
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    cmp eax, 0
    je for_41_end
    push offset var_p
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 8
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    push offset var_p
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 8
    imul eax, ebx
    pop ebx
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -4]
    pop eax
    neg eax
    push eax
    push offset var_p
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 8
    imul eax, ebx
    pop ebx
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
for_41_inc:
    push eax
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_41_cond
for_41_end:
    mov eax, 9
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
for_18467_start:
for_18467_cond:
    push eax
    mov eax, 1
    neg eax
    mov ebx, eax
    push dword ptr [ebp + -4]
    pop eax
    cmp eax, ebx
    mov eax, 0
    setg al
    cmp eax, 0
    je for_18467_end
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push dword ptr [eax + 0]
    pop eax
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_47
    add esp, 8
for_18467_inc:
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    sub eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_18467_cond
for_18467_end:
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