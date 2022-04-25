%ifdef COMMENT
    ////////////////////////////////////
    a, b, c, d - byte, e, f, g, h - word
    2.8. 2 * (a + b) - e
    a = 104, b = 59, e = 44 =>
           => res = 2 * 163 - 44 =>
           => res = 326 - 44 =>
           => res = 282 = 011A(16)
    /////////////////////////////////////
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
        a db 104
        b db 59
        e dw 44
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        
        mov AL, byte [a]
        add AL, byte [b]
        mov AH, 2
        mul AH ; AX <- AL * AH = 2 * (a + b)
        
        sub AX, word [e]
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
