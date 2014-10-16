.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_12 db "%d", 0

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
    mov eax, 5
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
    jmp while_41_cond
while_41_end:
    push dword ptr [ebp + -4]
    invoke crt_printf, addr var_12
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