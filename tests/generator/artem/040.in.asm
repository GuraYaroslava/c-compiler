.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_42 db "%d %d %d %d", 0

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 48
    mov eax, ebp
    mov ebx, -40
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
    mov eax, ebp
    mov ebx, -48
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -40
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
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, 3
    push eax
    pop eax
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -40
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
    mov eax, 15
    push eax
    mov eax, ebp
    mov ebx, -40
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
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    push dword ptr [ebp + -44]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    push dword ptr [ebp + -48]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    pop ebx
    pop eax
    add eax, ebx
    push eax
    push dword ptr [ebp + -44]
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -40
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
    pop eax
    neg eax
    push eax
    push dword ptr [ebp + -44]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    pop ebx
    pop eax
    cdq
    imul ebx
    push eax
    push dword ptr [ebp + -48]
    pop eax
    pop ebx
    mov dword ptr [eax + 0], ebx
    mov eax, ebx
    push eax
    mov eax, ebp
    mov ebx, -40
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
    push dword ptr [ebp + -48]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    mov eax, ebp
    mov ebx, -40
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
    push dword ptr [ebp + -44]
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    invoke crt_printf, addr var_42
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