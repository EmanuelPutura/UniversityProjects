%ifdef COMMENT
    1.8. (a+b-d)+(a-b-d)
        a,b,c,d - byte
        a = 10, b = 5, d = 2 => rez = 13 + 3 = 16
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
        d db 2
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov EBX, 0
        
        mov AL, byte [a]
        add AL, byte [b]
        sub AL, byte [d]
        
        mov BL, byte [a]
        sub BL, byte [b]
        sub BL, byte [d]
        
        add AL, BL
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
