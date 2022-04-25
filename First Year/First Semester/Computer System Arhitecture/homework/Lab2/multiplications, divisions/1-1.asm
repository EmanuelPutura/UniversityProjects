%ifdef COMMENT
    1.1. ((a+b-c)*2 + d-5)*d
        a,b,c - byte, d - word
        a = 10, b = 7, c = 2, d = 10
%endif

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        a db 10
        b db 7
        c db 2
        d dw 10
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov AL, byte [a]
        add AL, byte [b] ; AL <- [a] + [b]
        sub AL, byte [c] ; AL <- [a] + [b] - [c]
        
        mov EBX, 0
        mov BL, 2
        mul BL ; AX <- AL * BL = (a + b - c) * 2
        
        add AX, word [d] ; AX <- AX + [d] = (a + b - c) * 2 + d
        sub AX, 5 ; AX <- AX + [d] = (a + b - c) * 2 + d - 5
        mul word [d] ; DX:AX <- AX * [d] = ((a + b - c) * 2 + d - 5) * d
        
        push DX
        push AX
        pop EBX ; store the result in EBX
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
