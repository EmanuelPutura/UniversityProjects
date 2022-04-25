bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;Exercise 24:
;Given the doubleword M, compute the doubleword MNew as follows:
;the bits 0-3 a of MNew are the same as the bits 5-8 a of M. +
;the bits 4-7 a of MNew have the value 1 +
;the bits 27-31 a of MNew have the value 0 +
;the bits 8-26 of MNew are the same as the bits 8-26 a of M.

segment data use32 class=data
    ; ...
    M dd 100111010101110101001101110101b
    MNew dd 0
    a db 10
    L1 equ $ - $$
    L2 equ $$
; our code starts here
segment code use32 class=code
    start:
        ; ... 00000000000000000000000000000000
        ;mov eax, dword DS:[00401008]
        ;mov eax, 3-2
        
        mov eax, L1
        mov ecx, L2
        mov ebx, 0 ; we compute the result in ebx

        mov eax, [M] ; we isolate bits 5-8 of M
        and eax, 00000000000000000000000111100000b
        mov cl, 5
        ror eax, cl ; we rotate 5 positions to the right
        or ebx, eax ; we put the bits into the result

        or ebx, 00000000000000000000000011110000b ; we force the value of bits 4-7 of the result to the value 1
        
        and ebx, 00000111111111111111111111111111b; we force the value of bits 27-31 of the result to the value 0

        mov eax, [M] ; we isolate bits 8-26 of M
        and eax, 00000111111111111111111100000000b
        or ebx, eax ; we put the bits into the result

        mov [MNew], ebx ; we move the result from the register to the result variable

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program