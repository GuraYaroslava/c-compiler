.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_17 db "%d %d %d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 48
    mov eax, 1
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
    mov eax, ebp
    mov ebx, -44
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
    pop eax
    push dword ptr [eax + 0]
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
    pop eax
    mov ebx, eax
    mov eax, dword ptr [ebx + 0]
    push eax
    invoke crt_printf, addr var_17
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