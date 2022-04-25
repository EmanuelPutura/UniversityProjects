bits 32

extern _printf

; int printWithFormat(const char* format, int number)
global _printWithFormat

segment code use32 class=code
    _printWithFormat:
        ; creating a stack frame for the called program
        push EBP
        mov EBP, ESP
        
        pushad ; save the registers
        
        mov EAX, dword [EBP + 8] ; EAX <- the offset of the format
        mov EBX, dword [EBP + 12] ; EBX <- the value of the number
        
        ; print the data, according to the given format saved in EAX
        push dword EBX
        push dword EBX
        push dword EAX
        call _printf
        add ESP, 4 * 3 ; restore the stack to its state before the printing
        
        popad ; restore the registers
        
        ; restore the stack frame for the caller program
        mov ESP, EBP
        pop EBP
        
        ret ; return