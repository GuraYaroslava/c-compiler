.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_16 db "%d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_five:
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
    mov eax, 10
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
    push dword ptr [ebp + -4]
    mov eax, ebp
    mov ebx, -8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
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
    jne if18467_true
    je if18467_false
if18467_true:
    jmp for_41_inc
    jmp if18467_end
if18467_false:
if18467_end:
    push dword ptr [ebp + -8]
    pop eax
    mov dword ptr [ebp + 8], eax
    jmp end_func_five
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
end_func_five:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 0
    sub esp, 4
    call func_five
    add esp, 0
    invoke crt_printf, addr var_16
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