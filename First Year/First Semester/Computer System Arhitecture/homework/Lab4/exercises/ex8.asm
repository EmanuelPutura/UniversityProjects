%ifdef COMMENT
    8. Given the words A and B, compute the byte C as follows:
        the bits 0-5 are the same as the bits 5-10 of A
        the bits 6-7 are the same as the bits 1-2 of B.
        Compute the doubleword D as follows:
        the bits 8-15 are the same as the bits of C
        the bits 0-7 are the same as the bits 8-15 of B
        the bits 24-31 are the same as the bits 0-7 of A
        the bits 16-23 are the same as the bits 8-15 of A.
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
        A dw 1101001011100101b ; D2E5h
        B dw 0010110000101111b ; 2C2F
        C resb 1 ; we reserve one byte
        D resw 2 ; we reserve two words, so basically we reserve one doubleword
; our code starts here
segment code use32 class=code
    start:
        mov BL, 0 ; we compute C in BL
        
        mov AX, word [A]
        and AX, 0000011111100000b ; we isolate the bits 5-10 of A
        mov CL, 5
        ror AX, CL ; AX <- 0000000000010111b (we rotate 5 positions to the right)
        or BL, AL ; BL <- 00010111b
        
        mov AX, word [B]
        and AL, 00000110b ; we isolate the bits 1-2 of B
        mov CL, 5
        rol AL, CL ; AL <- 11000000b (we rotate 5 positions to the left)
        or BL, AL ; BL <- 11010111b = D7h
        
        mov byte [C], BL ; we move the result into C. So we have that C = 11010111b = D7h
        
        mov EBX, 0 ; we compute D in EBX
        
        mov EAX, 0
        mov AL, byte [C] ; AL <- C => EAX = [C] = 00000000000000000000000011010111b
        mov CL, 8
        rol EAX, CL ; EAX <- 00000000000000001101011100000000b (we rotate 8 positions to the left)
        or EBX, EAX ; EBX <- 00000000000000001101011100000000b
        
        mov AX, word [B] ; AX <- 0010110000101111b
        and AX, 1111111100000000b ; we isolate the bits 8-15 of B
        mov CL, 8
        ror AX, CL ; AX <- 0000000000101100b (we rotate 8 positions to the right)
        or BL, AL ; BL <- 00101100b => EBX <- 00000000000000001101011100101100b
 
        mov EAX, 0
        mov AX, word [A] ; AX <- 1101001011100101b
        mov AH, 0 ; the bits 0-7 of AX are the bits of AL => we isolate the bits 0-7 of A
        mov CL, 24
        rol EAX, CL ; EAX <- 11100101000000000000000000000000b (we rotate 24 positions to the left)
        or EBX, EAX ; EBX <- 11100101000000001101011100101100b
        
        mov EAX, 0
        mov AX, word [A] ; AX <- 1101001011100101b
        mov AL, 0 ; the bits 8-15 of AX are the bits of AH => we isolate the bits 8-15 of A
        mov CL, 8
        rol EAX, CL ; EAX <- 00000000000000001101001000000000b (we rotate 8 positions to the left)
        or EBX, EAX ; EBX <- 11100101110100101101011100101100b = E5D2D72Ch
        
        mov dword [D], EBX ; We move the result into D. So we have 
                                    ; that D = 11100101110100101101011100101100b = E5D2D72Ch
                                    ; we also have that C = 11010111b = D7h
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
