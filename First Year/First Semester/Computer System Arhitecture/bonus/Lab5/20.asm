%ifdef
    20. Two byte strings A and B are given. Obtain the string R by concatenating the elements of B in reverse order 
    and the even elements of A.
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
        A db 2, 1, 3, 3, 4, 2, 6
        LA equ $ - A
        B db 4, 5, 7, 6, 2, 1
        LB equ $ - B
        R resb LA + LB
; our code starts here
segment code use32 class=code
    start:
        mov ECX, LB
        mov ESI, LB - 1
        mov EDI, 0
        jecxz final_1
        
        B_loop:
            mov AL, [B + ESI]
            mov [R + EDI], AL
            dec ESI
            inc EDI
        loop B_loop
        
        final_1:
        mov ECX, LA
        mov ESI, 0
        jecxz final_2
        
        A_loop:
            mov AL, [A + ESI]
            mov BL, AL
            cbw
            mov BH, 2
            idiv BH
            mov AL, BL
            cmp AH, 0
            jz is_even
            return:
                inc ESI
        loop A_loop
        jmp final_2
        
        is_even:
            mov [R + EDI], AL
            inc EDI
            jmp return
        
        final_2:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
