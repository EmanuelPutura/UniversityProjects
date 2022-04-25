%ifdef COMMENT
    Read a decimal number from the keyboard and print it in hexadecimal format.
%endif

bits 32

global start        

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
        number resd 1
        format_scanf db "%d", 0
        format_printf db "%x", 0
segment code use32 class=code
    start:
        push dword number
        push dword format_scanf
        call [scanf]
        add esp, 4 * 2
        
        push dword [number]
        push dword format_printf
        call [printf]
        add esp, 4 * 2
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
