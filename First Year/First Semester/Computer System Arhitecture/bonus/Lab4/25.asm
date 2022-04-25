%ifdef COMMENT
    25. Given the doublewords M and N, compute the doubleword P as follows.
    the bits 0-6 of P are the same as the bits 10-16 of M
    the bits 7-20 of P are the same as the bits 7-20 of (M AND N).
    the bits 21-31 of P are the same as the bits 1-11 of N.
    
    ex: M dd 1101 1100 0011 1010 1000 1101 1011 1110b
        N dd 1111 1000 1010 1110 1101 1100 0011 1010b
    =>  M AND N = 1101 1000 0010 1010 1000 1100 0011 1010b
        P =  1100 0011 1010 1010 1000 1100 0010 0011b
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
        M dd 11011100001110101000110110111110b
        N dd 11111000101011101101110000111010b
        P resw 2
; our code starts here
segment code use32 class=code
    start:
        mov EBX, 0
        
        mov AX, [M + 1]
        mov CL, 2
        shr AX, CL
        and AX, 01111111b
        or BX, AX
        
        mov EAX, [M]
        and EAX, [N]
        and EAX, 00000000000111111111111110000000b
        or EBX, EAX
        
        mov EAX, 0
        mov AX, [N]
        mov CL, 1
        shr AX, CL
        and AX, 0000011111111111b
        mov CL, 21
        shl EAX, CL
        or EBX, EAX
                
        mov [P], EBX        
                
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
