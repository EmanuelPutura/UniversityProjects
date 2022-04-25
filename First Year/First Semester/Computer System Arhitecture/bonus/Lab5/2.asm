%ifdef COMMENT
    2. Given a character string S, obtain the string D containing all special characters (!@#$%^&*) of the string S.
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
        S db '+', '4', '2', 'a', '@', '3', '$', '*'
        L1 equ $ - S
        D resb L1
        SC db '!', '@', '#', '$', '%', '^', '&', '*'
        L2 equ $ - SC
; our code starts here
segment code use32 class=code
    start:
        mov ECX, L1
        mov ESI, 0
        mov EDI, 0
        
        S_loop:
            mov AL, [S + ESI]
            
            mov EBX, 0
            SC_loop:
                mov DL, [SC + EBX] 
                cmp AL, DL
                jz comp 
                inc EBX
                cmp EBX, L2
            jnz SC_loop
            jmp incr
            comp:
                mov [D + EDI], AL
                inc EDI
            incr:
                inc ESI
        loop S_loop
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
