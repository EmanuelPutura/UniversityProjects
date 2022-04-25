%ifdef COMMENT
    11. A byte string S is given. Obtain the string D1 which contains all the even numbers of S and the string D2 which contains all the odd numbers of S.
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
        S db 1, 5, 3, 8, 2, 9
        L equ $ - S
        D1 resb L
        D2 resb L
segment code use32 class=code
    start:
        mov ECX, L
        mov ESI, 0
        mov EDI, 0
        mov EBX, 0
        
        jecxz final
        S_loop:
            mov AL, [S + ESI]
            mov DH, AL
            cbw
            mov DL, 2
            idiv DL
            cmp AH, 0
            mov AL, DH
            jz D1_loop
            cmp AH, 1
            jz D2_loop
            return:
            inc ESI
        loop S_loop
        jmp final
        
        D1_loop:
            mov [D1 + EDI], AL
            inc EDI
            jmp return
        D2_loop:
            mov [D2 + EBX], AL
            inc EBX
            jmp return
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
