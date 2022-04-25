%ifdef COMMENT
    a - dword, b, d - byte, c - word, e - qword
    a + b / c - d * 2 - e
    
    a = 200, b = 100, c = 5, d = 5, e = 100
    => res = 200 + 100 / 5 - 5 * 2 - 100 
    => res = 200 + 20 - 10 - 100
    => res = 110 = C8(H)
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
        a dd 200
        b db 100
        c dw 5
        d db 5
        e dq 100
; our code starts here
segment code use32 class=code
    start:
        mov AL, byte [b]
        mov AH, 0 ; unsigned conversion from AL to AX
        mov DX, 0 ; unsigned conversion from AX to DX:AX
        div word [c] ; AX = b / c, DX = b % c
        bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

        mov BX, AX
        mov AL, 2
        mul byte [d] ; AX = d * 2
        sub BX, AX ; BX = b / c - d * 2
        mov AX, BX ; BX = b / c - d * 2
        
        mov DX, 0 ; unsigned conversion from BX to DX:BX
        add AX, word [a]
        adc DX, word [a + 2] ; DX:AX = a + b / c - d * 2
        
        push DX
        push AX
        pop EAX ; EAX = DX:AX = a + b / c - d * 2
        
        mov EDX, 0 ; unisgned conversion from EAX to EDX:EAX
        sub EAX, dword [e]
        sbb EDX, dword [e + 4] ; EDX:EAX = a + b / c - d * 2 - e
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
