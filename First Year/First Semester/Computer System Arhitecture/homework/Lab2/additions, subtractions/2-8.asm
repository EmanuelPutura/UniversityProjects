%ifdef COMMENT
    2.8. (b+c+d)-(a+a)
        a,b,c,d - word
        a = 10, b = 15, c = 22, d = 23
        => res = 60 - 20 = 40
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
        a dw 10
        b dw 15
        c dw 22
        d dw 23
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov EBX, 0
        
        mov AX, [a]
        add AX, [a]
        
        mov BX, [b]
        add BX, [c]
        add BX, [d]
        
        sub BX, AX
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
