.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_12 db "%d is even", 0dh, 0ah, 0
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
    mov eax, 11
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
    sub esp, 0
    push dword ptr [ebp + -4]
    mov eax, 1
    push eax
    pop ebx
    pop eax
    and eax, ebx
    push eax
    pop eax
    cmp eax, 0
    jne if18467_true
    je if18467_false
if18467_true:
    sub esp, 0
    jmp for_41_inc
    jmp if18467_end
if18467_false:
if18467_end:
    push dword ptr [ebp + -4]
    invoke crt_printf, addr var_12
    add esp, 4
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