%ifdef COMMENT
    a, b, c, d - byte, e, f, g, h - word
    2.29. [b * c - (e + f)] / (a + d)
        a = 15, b = 12, c, = 12, d = 5, e = 91, f = 3
        => res = (144 - 94) / 20 = 50 / 20 = 2, r = 10
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
        a db 15
        b db 12
        c db 12
        d db 5
        e dw 91
        f dw 3
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov AL, byte [b]
        mul byte [c] ; AX <- AL * [c] = b * c
        
        mov EBX, 0
        mov BX, word [e]
        add BX, word [f] ; BX <- BX + [f] = e + f
        sub AX, BX ; AX <- AX - BX = b * c - (e + f)
        
        mov EBX, 0
        mov BL, byte [a]
        add BL, byte [d] ; BL <- BL + [d] = a + d
        div BL ; AL <- AX / BL = [b * c - (e + f)] / (a + d)
               ; AH <- AX % BL = [b * c - (e + f)] % (a + d)
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
