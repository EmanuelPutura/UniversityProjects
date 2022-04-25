%ifdef COMMENT
    32. A byte string S of length l is given. Obtain the string D of length l-1, such that each element of D is the quotient of two consecutive elements of S, i.e. D(i) = S(i) / S(i+1).
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
        S db 12, 6, 3, 1
        L equ $ - S
        D resb L - 1
; our code starts here
segment code use32 class=code
    start:
        mov ECX, L - 1
        mov ESI, 0
        mov EDI, 0
        jecxz final
        
        S_loop:
            mov AL, [S + ESI]
            cbw
            mov BL, [S + ESI + 1]
            idiv BL
            mov [D + EDI], AL
            inc EDI
            inc ESI
        loop S_loop
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
