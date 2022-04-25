%ifdef COMMENT
    a - byte, b - word, c - double word, d - qword - Unsigned representation
    1.8. N = (a + b - d) + (a - b - d)
        a = 200, b = 50, d = 100 =>
            => N = 150 + 50 =>
            => N = 200 (qword)
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
        a db 200
        b dw 50
        d dq 100
; our code starts here
segment code use32 class=code
    start:
        mov AL, byte [a] ; AL = a
        mov AH, 0 ; unsigned conversion from AL to AX
        add AX, word [b] ; AX = a + b
        
        mov DX, 0 ; unsigned conversion from AX to DX:AX
        
        push DX
        push AX
        pop EAX ; EAX = a + b
        
        mov EDX, 0 ; unsigned conversion from EAX to EDX:EAX
        sub EAX, dword [d]
        sbb EDX, dword [d + 4] ; EDX:EAX = a + b - d 
        
        mov BL, byte [a] ; BL = a
        mov BH, 0 ; unisigned conversion from BL to BX
        sub BX, word [b] ; BX = a - b
        
        mov CX, 0 ; unsigned conversion from BX to CX:BX
        
        push CX
        push BX 
        pop EBX ; EBX = a - b
        
        mov ECX, 0 ; unsigned conversion from EBX to ECX:EBX
        sub EBX, dword [d]
        sbb ECX, dword [d + 4] ; ECX:EBX = a - b - d
        
        add EAX, EBX
        adc EDX, ECX ; EDX:EAX = (a + b - d) + (a - b - d)
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
