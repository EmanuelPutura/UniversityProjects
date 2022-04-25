%ifdef COMMENT
    8. A natural number a (a: dword, defined in the data segment) is given. Read a natural number b from the keyboard and calculate: a + a/b. Display the result of this operation. The values will be displayed in decimal format (base 10) with sign.
%endif

bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
        a dd -180
        b resd 1
        message db "a + a/b = %d", 0
        format db "%d", 0
segment code use32 class=code
    start:
        mov EAX, [a] 
        PUSHAD ; save the value of the general registers
        
        ; reading
        push dword b ; the address of b
        push dword format
        call [scanf]
        add ESP, 4 * 2
        
        POPAD ; restore the value of the general registers
        
        mov EBX, EAX ; save a copy of EAX in EBX
        cdq ; signed conversion from EAX to EDX:EAX
        idiv dword [b] ; EAX = EDX:EAX / b, EDX = EDX:EAX % b
        add EBX, EAX ; EBX = EBX + EAX = a + a / b
        
        ; writting
        push EBX
        push dword message
        call [printf]
        add ESP, 4 * 2
        
        push    dword 0
        call    [exit]
