; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a - doubleword; b, d - byte; c - word; e - qword
; a + b / c - d * 2 - e

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        a dd 125
        b db 2
        c dw 15
        d db 200
        e dq 80
; our code starts here
segment code use32 class=code
    start:
        mov AL, byte [b] ; AL = b
        cbw ; signed conversion from AL to AX
        cwd ; signed conversion from AX to DX:AX
        idiv word [c] ; AX = DX:AX / [c] = b / c
        
        mov BX, AX ; BX = b / c
        mov AL, 2 ; AL = 2
        imul byte [d] ; AX = d * 2
        sub BX, AX ; BX = b / c - d * 2
        mov AX, BX ; AX = b / c - d * 2
  
        cwde ; signed conversion from AX to EAX
        add EAX, dword [a] ; EAX = a + b / c - d * 2
        cdq ; signed conversion from EAX to EDX:EAX
        
        sub EAX, dword [e]
        sbb EDX, dword [e + 4]
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
