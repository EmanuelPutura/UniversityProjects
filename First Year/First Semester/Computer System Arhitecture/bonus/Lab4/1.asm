%ifdef COMMENT
    1. Given the words A and B, compute the doubleword C as follows:
    the bits 0-4 of C are the same as the bits 11-15 of A
    the bits 5-11 of C have the value 1
    the bits 12-15 of C are the same as the bits 8-11 of B
    the bits 16-31 of C are the same as the bits of A
    
    ex: A dw 1101 1100 0011 1010b
        B dw 1001 0001 1111 1110b
    =>  C =  1101 1100 0011 1010 0001 1111 1111 1011b
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
        A dw 1101110000111010b
        B dw 1001000111111110b
        C resd 1
; our code starts here
segment code use32 class=code
    start:
        mov EBX, 0
        mov AX, [A]
        mov CL, 11
        shr AX, CL
        and AX, 0000000000011111b
        mov BX, AX
        
        or BX, 0000111111100000b
        
        mov AX, [B]
        mov CL, 4
        shl AX, CL
        and AX, 1111000000000000b
        or BX, AX
        
        mov DX, [A]
        push DX
        push BX
        pop EBX
        
        mov [C], EBX
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
