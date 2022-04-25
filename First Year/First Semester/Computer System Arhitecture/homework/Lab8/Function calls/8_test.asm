; The following program should read a number and print the message together with the number on the screen.
bits 32
global start        

; declaring extern functions used in the program
extern exit, printf, scanf            
import exit msvcrt.dll     
import printf msvcrt.dll     ; indicating to the assembler that the printf fct can be found in the msvcrt.dll library
import scanf msvcrt.dll      ; similar for scanf
                          
segment  data use32 class=data
	message  db "Numarul citit este n= %d", 0
    n dd 0       ; this is the variable where we store the number read from keyboard    
	format  db "%d", 0  ; %d <=> a decimal number (base 10)
    
segment  code use32 class=code
    start:
        mov eax, [DS:ebx]                               
        ; calling scanf(format, n) => we read the number and store it in the variable n
        ; push parameters on the stack from right to left
        push  dword n       ; ! address of n, not the value
        push  dword format
        call  [scanf]       ; call scanf for reading
        add  esp, 4 * 2     ; taking parameters out of the stack; 4 = dimension of a dword; 2 = nr of parameters
        
        push  dword 0     ; push the parameter for exit on the stack
        call  [exit]       ; call exit