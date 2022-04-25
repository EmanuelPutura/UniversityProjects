%ifdef COMMENT
    25. Two character strings S1 and S2 are given. Obtain the string D which contains all the elements of S1 that do not appear in S2.
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
        S1 db '+', '4', '2', 'a', '8', '4', 'X', '5'
        L1 equ $ - S1
        S2 db 'a', '4', '5'
        L2 equ $ - S2
        D resb L1
; our code starts here
segment code use32 class=code
    start:
        mov ECX, L1
        mov ESI, 0
        mov EDI, 0
        jecxz final
        
        S1_loop:
            mov AL, [S1 + ESI]
            
            mov EBX, 0
            S2_loop:
                mov AH, [S2 + EBX]
                
                cmp AL, AH
                je final_2
                
                inc EBX
                cmp EBX, L2
            jne S2_loop
            
            mov [D + EDI], AL
            inc EDI
            final_2:
        inc ESI
        loop S1_loop
       
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
