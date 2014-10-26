.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "%d %d %d", 0dh, 0ah, 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_print:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_0
    add esp, 12
    mov eax, 0
    push eax
    pop eax
    mov dword ptr [ebp + 20], eax
    jmp end_func_print
end_func_print:
    mov esp, ebp
    pop ebp
    ret 0
func_mult:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
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
    jmp end_func_mult
end_func_mult:
    mov esp, ebp
    pop ebp
    ret 0
func_div:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 4
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
    mov dword ptr [ecx + 0], eax
    mov eax, ebp
    mov ebx, 20
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    idiv ebx
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
    jmp end_func_div
end_func_div:
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
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -12
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
    mov eax, 2
    push eax
    pop eax
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -12
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    push eax
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    push eax
    pop eax
    mov ebx, 0
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 2
    push eax
    pop eax
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -24
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
    mov eax, 1
    push eax
    pop eax
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -24
    add eax, ebx
    push eax
    pop eax
    mov ebx, 8
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    call func_print
    add esp, 12
    sub esp, 4
    push dword ptr [ebp + -16]
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    call func_print
    add esp, 12
    sub esp, 4
    sub esp, 12
    push dword ptr [ebp + -16]
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    call func_mult
    add esp, 24
    call func_print
    add esp, 12
    sub esp, 4
    sub esp, 12
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push dword ptr [ebp + -16]
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    call func_mult
    add esp, 24
    call func_print
    add esp, 12
    sub esp, 4
    sub esp, 12
    push dword ptr [ebp + -16]
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    call func_div
    add esp, 24
    call func_print
    add esp, 12
    sub esp, 4
    sub esp, 12
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push dword ptr [ebp + -16]
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    call func_div
    add esp, 24
    call func_print
    add esp, 12
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