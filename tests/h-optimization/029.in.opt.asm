.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_9 db "one _ start", 0dh, 0ah, 0
    var_14 db "two _ start", 0dh, 0ah, 0
    var_21 db "one", 0dh, 0ah, 0
    var_28 db "two", 0dh, 0ah, 0
    var_35 db "three", 0dh, 0ah, 0
    var_40 db "while #three", 0dh, 0ah, 0
    var_45 db "two _ end", 0dh, 0ah, 0
    var_47 db "one _ end", 0
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
while_41_start:
while_41_cond:
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
    je while_41_end
    sub esp, 0
    invoke crt_printf, addr var_9
    add esp, 0
while_18467_start:
while_18467_cond:
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
    je while_18467_end
    sub esp, 0
    invoke crt_printf, addr var_14
    add esp, 0
while_6334_start:
while_6334_cond:
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
    je while_6334_end
    sub esp, 0
    invoke crt_printf, addr var_40
    add esp, 0
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
    jmp while_6334_cond
while_6334_end:
    invoke crt_printf, addr var_45
    add esp, 0
    jmp while_18467_cond
while_18467_end:
    invoke crt_printf, addr var_47
    add esp, 0
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