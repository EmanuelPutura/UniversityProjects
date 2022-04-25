; The code below will print message ”n=”, then will read from keyboard the value of perameter n.
bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
        
segment code use32 class=code
    start:
        mov eax, -24 // 3
        
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program