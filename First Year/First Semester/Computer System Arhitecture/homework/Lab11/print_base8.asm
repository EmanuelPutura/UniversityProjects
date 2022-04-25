bits 32

extern printf
import printf msvcrt.dll

global print_b8

segment data use32 public data
        format_b8 db "The value in base 8 for %d is %o", 10, 0
segment code use32 public code
    print_b8:
        mov ECX, dword [ESP + 4] ; store the first parameter of the procedure into ECX
        
        push dword ECX           ; third parameter of printf - the decimal value of ECX
        push dword ECX           ; second parameter of printf - the octal value of ECX
        push dword format_b8     ; first parameter of printf - the format
        call [printf]            ; call printf function
        add esp, 4 * 3           ; restore the initial value of ESP
        
        ret                      ; return