%ifdef COMMENT
    a - byte, b - word, c - double word, d - qword - Signed representation
    2.8. N = (b + c + d) - (a + a)
        a = -50, b = 100, c = 200, d = -500 =>
            => N = -200 + 100 =>
            => N = -100 (qword) = (FF FF FF FF FF FF FF 9C)(H)
        
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
        a db -50
        b dw 100
        c dd 200
        d dq -500
; our code starts here
segment code use32 class=code
    start:
        mov AX, word [b] ; AX = b
        cwde ; signed conversion from AX to EAX
        add EAX, dword [c] ; EAX = b + c
        cdq  ; signed conversion from EAX to EDX:EAX
        
        add EAX, dword [d] 
        adc EDX, dword [d + 4] ; EDX:EAX = b + c + d
        mov ECX, EDX
        mov EBX, EAX ; ECX:EBX = b + c + d
        
        mov AL, byte [a] ; AL = a
        add AL, byte [a] ; AL = a + a
        cbw  ; signed conversion from AL to AX
        cwde ; signed conversion from AX to EAX
        cdq  ; signed conversion from EAX to EDX:EAX
        
        sub EBX, EAX
        sbb ECX, EDX ; ECX:EBX = b + c + d - (a + a)
        
        mov EDX, ECX
        mov EAX, EBX ; EDX:EBX = b + c + d - (a + a)
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
