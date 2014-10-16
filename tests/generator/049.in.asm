.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_52 db "%d %d %d %d %d %d %d %d", 0dh, 0ah, 0
    var_a dd 1700 dup(0)
    var_b dd 17 dup(0)

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, 1000
    push eax
    pop eax
    neg eax
    push eax
    push offset var_b
    pop eax
    mov ebx, 52
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    pop eax
    mov ebx, 12
    add eax, ebx
    push eax
    mov eax, 0
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push offset var_b
    pop eax
    mov ebx, 0
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
    mov eax, 100
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    pop eax
    cmp eax, 0
    je for_41_end
    push dword ptr [var_b + 64]
    push dword ptr [var_b + 60]
    push dword ptr [var_b + 56]
    push dword ptr [var_b + 52]
    push dword ptr [var_b + 48]
    push dword ptr [var_b + 44]
    push dword ptr [var_b + 40]
    push dword ptr [var_b + 36]
    push dword ptr [var_b + 32]
    push dword ptr [var_b + 28]
    push dword ptr [var_b + 24]
    push dword ptr [var_b + 20]
    push dword ptr [var_b + 16]
    push dword ptr [var_b + 12]
    push dword ptr [var_b + 8]
    push dword ptr [var_b + 4]
    push dword ptr [var_b + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    pop ebx
    mov dword ptr [eax + 4], ebx
    pop ebx
    mov dword ptr [eax + 8], ebx
    pop ebx
    mov dword ptr [eax + 12], ebx
    pop ebx
    mov dword ptr [eax + 16], ebx
    pop ebx
    mov dword ptr [eax + 20], ebx
    pop ebx
    mov dword ptr [eax + 24], ebx
    pop ebx
    mov dword ptr [eax + 28], ebx
    pop ebx
    mov dword ptr [eax + 32], ebx
    pop ebx
    mov dword ptr [eax + 36], ebx
    pop ebx
    mov dword ptr [eax + 40], ebx
    pop ebx
    mov dword ptr [eax + 44], ebx
    pop ebx
    mov dword ptr [eax + 48], ebx
    pop ebx
    mov dword ptr [eax + 52], ebx
    pop ebx
    mov dword ptr [eax + 56], ebx
    pop ebx
    mov dword ptr [eax + 60], ebx
    pop ebx
    mov dword ptr [eax + 64], ebx
    mov eax, ebx
    push eax
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
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_41_cond
for_41_end:
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
for_18467_start:
for_18467_cond:
    push dword ptr [ebp + -4]
    mov eax, 100
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
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 52
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 52
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 12
    add eax, ebx
    push eax
    mov eax, 9
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 12
    add eax, ebx
    push eax
    mov eax, 5
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 12
    add eax, ebx
    push eax
    mov eax, 0
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    push offset var_a
    push dword ptr [ebp + -4]
    pop eax
    mov ebx, 68
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_52
    add esp, 32
for_18467_inc:
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
    add eax, ebx
    mov dword ptr [ecx + 0], eax
    jmp for_18467_cond
for_18467_end:
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