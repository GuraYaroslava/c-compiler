.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_9 db "one _ start", 0dh, 0ah, 0
    var_23 db "two _ start", 0dh, 0ah, 0
    var_40 db "three", 0dh, 0ah, 0
    var_42 db "two _ end", 0dh, 0ah, 0
    var_44 db "one _ end", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

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
for_41_start:
for_41_cond:
    push dword ptr [ebp + -4]
    mov eax, 0
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    sete al
    push eax
    pop eax
    cmp eax, 0
    je for_41_end
    sub esp, 4
    invoke crt_printf, addr var_9
    add esp, 0
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
    mov eax, 0
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
for_18467_start:
for_18467_cond:
    push dword ptr [ebp + -8]
    mov eax, 2
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    pop eax
    cmp eax, 0
    je for_18467_end
    sub esp, 4
    invoke crt_printf, addr var_23
    add esp, 0
    mov eax, 0
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
for_6334_start:
for_6334_cond:
    push dword ptr [ebp + -12]
    mov eax, 3
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    pop eax
    cmp eax, 0
    je for_6334_end
    sub esp, 0
    invoke crt_printf, addr var_40
    add esp, 0
for_6334_inc:
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_6334_cond
for_6334_end:
    invoke crt_printf, addr var_42
    add esp, 0
for_18467_inc:
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_18467_cond
for_18467_end:
    invoke crt_printf, addr var_44
    add esp, 0
for_41_inc:
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    sub eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_41_cond
for_41_end:
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