%ifdef COMMENT
    b) signed
    a, b - word / c, d - byte / e - dword / x - qword
    1.8. 1 / a + 200 * b - c / (d + 1) + x / a - e
        => res = 1 / 100 + 200 * (-5) - 120 / (59 + 1) + 1000 / 100 - 100
        => res = -1000 - 2 + 10 - 100
        => res = -1002 + 10 - 100
        => res = -992 - 100 
        => res = -1092
    
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
        a dw 100
        b dw -5 
        c db 120
        d db 59
        x dq 1000
        e dd 100
; our code starts here
segment code use32 class=code
    start:
        mov AX, 1 ; AX = 1
        cwd ; signed conversion from AX to DX:AX
        idiv word [a] ; AX = 1 / a
        mov BX, AX ; BX =bits 32 ; assembling for the 32 bits architecture

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
        mov AX, 200 ; AX = 200
        imul word [b] ; DX:AX = 200 * b
        add AX, BX
        adc DX, 0 ; DX:AX = 1 / a + 200 * b
        
        push DX
        push AX
        pop EBX ; EBX = 1 / a + 200 * b
        
        mov AL, byte [c] ; AL = c
        cbw ; signed conversion from AL to AX
        add byte [d], 1 ; d = d + 1
        idiv byte [d] ; AL = c / (d + 1)
        cbw ; signed conversion from AL to AX
        cwde ; signed conversion from AX to EAX
        
        sub EBX, EAX ; EBX = 1 / a + 200 * b - c / (d + 1)
        
        mov AX, word [a] ; AX = a
        cwde ; signed conversion from AX to EAX
        mov ECX, EAX ; ECX = a
        
        mov EAX, dword [x]
        mov EDX, dword [x + 4] ; EDX:EAX = x
        idiv ECX ; EAX = x / a
        
        add EBX, EAX ; EBX = 1 / a + 200 * b - c / (d + 1) + x / a
        sub EBX, dword [e] ; EBX = 1 / a + 200 * b - c / (d + 1) + x / a - e
        
        mov EAX, EBX ; EAX = 1 / a + 200 * b - c / (d + 1) + x / a - e
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
