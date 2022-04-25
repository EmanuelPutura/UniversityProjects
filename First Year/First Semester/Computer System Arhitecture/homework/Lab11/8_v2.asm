bits 32

global start        

extern exit, printWithFormat
import exit msvcrt.dll

segment data use32 class=data
        format_b8 db "%d (in base 10) = %o (in base 8)", 10, 13, 0
        format_ascii db "The character with the ASCII code %d is %c", 10, 10, 13, 0
segment code use32 class=code
    start:
        mov ECX, 32 ; the starting number
        loop_nos:
            pushad
            ;push ECX ; store the value of ECX
            push dword ECX ; the number to be printed
            push format_b8 ; the format for printing the number in base 8
            call printWithFormat ; call the printing function
            add ESP, 4 * 2 ; free the stack
            ;pop ECX ; restore the value of ECX
            popad
            
            pushad
            ;push ECX ; store the value of ECX
            push dword ECX ; the number to be printed
            push format_ascii ; the format for printing corresponding character
            call printWithFormat ; call the printing function
            add ESP, 4 * 2 ; free the stack
            ;pop ECX ; restore the value of ECX
            
            inc ECX ; increment the current number
            cmp ECX, 126 ; check if all the numbers have been looped
        jbe loop_nos ; if the current number is <= 126, then continue
        
        push    dword 0
