%ifdef COMMENT
    1.8. (100*a+d+5-75*b)/(c-5)
        a,b,c - byte, d - word
        a = 10, b = 5, c = 9, d = 7 
        => res = (1000 + 7 + 5 - 375) / 4 =
               = (1012 - 375) / 4 =
               = 637 / 4 =
               = 159, r = 1
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
        b db 5
        c db 9
        d dw 7
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov EBX, 0
        
        mov AL, byte [a]
        mov BL, 100
        mul BL ; AX <- AL * BL = a * 100
        
        mov BX, word [d]
        add AX, BX
        add AX, 5 ; AX = 100 * a + d + 5
        mov BX, AX ; BX = 100 * a + d + 5
        
        mov EAX, 0
        mov AL, 75
        mul byte [b]
        sub BX, AX
        mov AX, BX ; AX <- 100 * a + d + 5 - 75 * b
        mov EBX, 0
        
        mov BL, byte [c]
        sub BL, 5 ; BL <- c - 5
        
        div BL ; AL <- (100 * a + d + 5 - 75 * b) / (c - 5) = 159 = 9F(16)
               ; AH <- (100 * a + d + 5 - 75 * b) % (c - 5) = 1 = 1(16)
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
