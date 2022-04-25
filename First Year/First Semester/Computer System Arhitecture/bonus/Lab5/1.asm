%ifdef COMMENT
    1. Given a byte string S of length L, obtain the string D of length L-1 as D(i) = S(i) * S(i+1) (each element of D is the product of two consecutive elements of S).
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
        S db 1, 2, 3, 4
        L equ $ - S
        D resw L - 1
; our code starts here
segment code use32 class=code
    start:
        mov ECX, L - 1
        jecxz final
        
        mov ESI, 0
        mov EDI, 0
        
        S_loop:
            mov AL, [S + ESI]
            mul byte [S + ESI + 1]
            mov [D + EDI], AX
            
            inc ESI
            inc EDI
        loop S_loop
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
