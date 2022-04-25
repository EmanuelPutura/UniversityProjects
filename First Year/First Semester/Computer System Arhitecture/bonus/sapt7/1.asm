%ifdef COMMENT
    Se da un string S. Sa se copieze caracterele din S in D, fiecare caracter fiind dublat. Elementele din S sunt word-uri.
    Elementele din D sunt octeti.
    
    ex: S dw '1', '2', 'c', '4', 'e'
    =>  D = '1', '1', '2', '2', 'c', 'c', '4', '4', 'e', 'e'
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
        S dw '1', '2', 'c', '4', 'e'
        L equ ($ - S) / 2
        D resb L
; our code starts here
segment code use32 class=code
    start:
        mov EDI, 0
        mov ESI, 0
        mov ECX, L
        jecxz prog_final
        
        S_loop:
            mov AX, [S + EDI]
            mov [D + ESI], AX
            add ESI, 1
            mov [D + ESI], AX
            add ESI, 1
            add EDI, 2
        loop S_loop
        prog_final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
