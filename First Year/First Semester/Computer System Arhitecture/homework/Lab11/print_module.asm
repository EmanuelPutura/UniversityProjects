bits 32

extern printf
import printf msvcrt.dll

segment code use32 class=code
    global printWithFormat
    
    ; int printWithFormat(const char* format, int number)
    printWithFormat:
        mov EAX, dword [ESP + 4] ; EAX <- the offset of the format
        mov EBX, dword [ESP + 8] ; EBX <- the value of the number
        
        ; print the data, according to the given format saved in EAX
        push dword EBX
        push dword EBX
        push dword EAX
        call [printf]
        add ESP, 4 * 2 ; restore the stack to its state before the printing
        
        ret ; return