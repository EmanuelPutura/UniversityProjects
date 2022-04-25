; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a - byte, b - word
; (b / a * 2 + 10) * b - b * 15;
; ex. 1: a = 10; b = 40; Result: (40 / 10 * 2 + 10) * 40 - 40 * 15 = 18 * 40 - 1600 = 720 - 600 = 120
; ex. 2: a = 100; b = 50; Result: (50 / 100 * 2 + 10) * 50 - 50 * 15 = 12 * 50 - 750 = 600 - 750 = - 150

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
        b dw 40
; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov AX, word [b]
        mov ECX, 0
        mov CL, byte [a]
        div CL ; AL = AX / CL = b / a
        
        mov AH, 2
        mul AH ; AX = AL * AH = (b / a) * 2
        
        mov ECX, 0
        mov CX, 10
        add AX, CX ; AX = AX + CX = b / a * 2 + 10
        
        mov ECX, 0
        mov CX, word [b]
        mul CX ; DX:AX = AX * CX = (b / a * 2 + 10) * b
        
        push DX
        push AX
        pop EBX ; EBX = DX:AX = (b / a * 2 + 10) * b
        
        mov EAX, 0
        mov AX, 15
        mul word [b] ; DX:AX = AX * [b] = 15 * b
        
        push DX
        push AX
        pop ECX ; ECX = DX:AX = 15 * b
        
        sub EBX, ECX
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
