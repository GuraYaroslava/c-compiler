.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_15 db "%d is odd", 0dh, 0ah, 0
    var_18 db "%d is even", 0dh, 0ah, 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, 10
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
    mov ebx, -4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
while_41_start:
while_41_cond:
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    pop ebx
    pop eax
    sub eax, ebx
    push eax
    pop eax
    cmp eax, 0
    je while_41_end
    sub esp, 0
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
    push dword ptr [ebp + -4]
    invoke crt_printf, addr var_15
    add esp, 4
    jmp if18467_end
if18467_false:
    push dword ptr [ebp + -4]
    invoke crt_printf, addr var_18
    add esp, 4
if18467_end:
    jmp while_41_cond
while_41_end:
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