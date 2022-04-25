bits 32
global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data segment data segment data
        c db 4, 5
        a db 1, 2, 3, 4
        b db 1, 2, 3, 4
        d dd $$
segment code use32 class=code
    start:
        push byte 13
        ; pop eip
        ; mov ax, a + b
        mov ah, a - $$ + b - $$
        mov bx, a - $$
        mov eax, $$
        mov edx, [d]
        ; mov bh, b - $$
        ; mov ax, [a - b]
        ; mov eax, [eax + ebx + a - 2]
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
