.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.data
    var_23 db "%d %d %d", 0
    helper4 real4 0.000000
    helper8 real8 0.000000

.code
func_main:
    push ebp
    mov ebp, esp
    sub esp, 44
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
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    mov eax, 3
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
    mov eax, 3
    push eax
    pop eax
    neg eax
    push eax
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    mov eax, 2
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
    mov ebx, -44
    add eax, ebx
    push eax
    mov eax, 4
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
    mov ebx, -44
    add eax, ebx
    push eax
    mov eax, 4
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    mov eax, 2
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    mov eax, ebp
    mov ebx, -44
    add eax, ebx
    push eax
    mov eax, 3
    push eax
    pop eax
    mov ebx, 4
    imul eax, ebx
    pop ebx
    add eax, ebx
    push eax
    pop eax
    push dword ptr [eax + 0]
    invoke crt_printf, addr var_23
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