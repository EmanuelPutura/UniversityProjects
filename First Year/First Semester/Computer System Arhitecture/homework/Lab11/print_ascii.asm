bits 32

extern printf
import printf msvcrt.dll

global print_ascii

segment data use32 public data
        format_ascii db "The character with the ASCII code %d is %c", 10, 10, 0
segment code use32 public code
    print_ascii:
        mov ECX, dword [ESP + 4] ; store the first parameter of the procedure into ECX
        
        push dword ECX           ; third parameter of printf - the decimal value of ECX
        push dword ECX           ; second parameter of printf - the character with the ASCII code equal to ECX
        push dword format_ascii  ; first parameter of printf - the format
        call [printf]            ; call printf function
        add esp, 4 * 3           ; restore the initial value of ESP
        
        ret                      ; return