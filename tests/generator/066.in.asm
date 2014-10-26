.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_32 db "%d %d", 0dh, 0ah, 0
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
    mov eax, 5
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
    sub esp, 4
    mov eax, 1
    push eax
    pop eax
    neg eax
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
while_18467_start:
while_18467_cond:
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -4]
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    pop eax
    cmp eax, 0
    je while_18467_end
    sub esp, 0
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
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -4]
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setl al
    push eax
    pop eax
    cmp eax, 0
    jne if6334_true
    je if6334_false
if6334_true:
    jmp while_18467_start
    jmp if6334_end
if6334_false:
if6334_end:
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -4]
    mov eax, 1
    push eax
    pop ebx
    pop eax
    add eax, ebx
    push eax
    pop ebx
    pop eax
    cmp eax, ebx
    mov eax, 0
    setge al
    push eax
    pop eax
    cmp eax, 0
    jne if26500_true
    je if26500_false
if26500_true:
    jmp while_18467_end
    jmp if26500_end
if26500_false:
if26500_end:
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    invoke crt_printf, addr var_32
    add esp, 8
    jmp while_18467_cond
while_18467_end:
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