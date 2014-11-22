.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_0 db "start: %d %d", 0dh, 0ah, 0
    var_12 db "end: %d %d", 0dh, 0ah, 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_print:
    push ebp
    mov ebp, esp
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_0
    add esp, 8
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_12
    add esp, 8
    mov eax, 0
    mov dword ptr [ebp + 24], eax
    jmp end_func_print
end_func_print:
    mov esp, ebp
    pop ebp
    ret 0
func_scale:
    push ebp
    mov ebp, esp
    push dword ptr [ebp + 24]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 24]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 24]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 24]
    mov eax, ebp
    mov ebx, 8
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov ecx, eax
    mov eax, dword ptr [ecx + 0]
    cdq
    imul ebx
    mov dword ptr [ecx + 0], eax
    push dword ptr [ebp + 20]
    push dword ptr [ebp + 16]
    push dword ptr [ebp + 12]
    push dword ptr [ebp + 8]
    pop eax
    mov dword ptr [ebp + 28], eax
    pop eax
    mov dword ptr [ebp + 32], eax
    pop eax
    mov dword ptr [ebp + 36], eax
    pop eax
    mov dword ptr [ebp + 40], eax
    jmp end_func_scale
end_func_scale:
    mov esp, ebp
    pop ebp
    ret 0
func_main:
    push ebp
    mov ebp, esp
    sub esp, 32
    mov eax, 0
    push eax
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -16
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 0
    push eax
    mov eax, ebp
    mov ebx, -32
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -32
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -32
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    mov ebx, 0
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 1
    push eax
    mov eax, ebp
    mov ebx, -32
    add eax, ebx
    mov ebx, 8
    add eax, ebx
    mov ebx, 4
    add eax, ebx
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    sub esp, 4
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    push dword ptr [ebp + -28]
    push dword ptr [ebp + -32]
    call func_print
    add esp, 16
    sub esp, 4
    sub esp, 16
    mov eax, 3
    push eax
    push dword ptr [ebp + -20]
    push dword ptr [ebp + -24]
    push dword ptr [ebp + -28]
    push dword ptr [ebp + -32]
    call func_scale
    add esp, 20
    call func_print
    add esp, 16
    sub esp, 4
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push dword ptr [ebp + -16]
    call func_print
    add esp, 16
    sub esp, 4
    sub esp, 16
    mov eax, 5
    push eax
    push dword ptr [ebp + -4]
    push dword ptr [ebp + -8]
    push dword ptr [ebp + -12]
    push dword ptr [ebp + -16]
    call func_scale
    add esp, 20
    call func_print
    add esp, 16
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