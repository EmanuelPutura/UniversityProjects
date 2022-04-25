%ifdef COMMENT
    8. Show for each number from 32 to 126 the value of the number (in base 8) and the character with that ASCII code.
%endif

bits 32

global start        

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

extern print_b8, print_ascii

segment code use32 class=code
    start:
        mov ECX, 32
        
        loop_nos:
            pushad ; store the general registers on the stack
            push dword ECX   ; the value of the current number
            call print_b8    ; call the print_b8 procedure
            add esp, 4 * 1   ; restore the initial value of ESP
            popad ; restore the general registers from the stack
                
            pushad ; store the general registers on the stack
            push dword ECX   ; the value of the current number
            call print_ascii ; call the print_ascii procedure
            add esp, 4 * 1   ; restore the initial value of ESP
            popad ; restore the general registers from the stack
            
            inc ECX
            cmp ECX, 126     ; if ECX > 126, stop the loop
        jbe loop_nos
     
        push    dword 0
        call    [exit]
