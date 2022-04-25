bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll

;24. Two numbers a and b are given. Compute the expression value: (a/b)*k, where k is a constant value defined in data segment. Display the expression value (in base 2).
                        
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
        a dd 0       ; defining the variables
        b dd 0
        k equ 5
		format  db "%d", 0  ; definining the format of the numbers that are given
        format2 db "The result of a/b*k is: %d", 0 ; defining the format of the result
        message1 db "a=", 0
        message2 db "b=", 0
; our code starts here
segment code use32 class=code
    start:
        push dword message1 ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4*1
        
        push dword a       ; pushing the parameters on the stack from right to left
		push dword format
		call [scanf]       ; calling the scanf function for reading
		add esp, 4 * 2     ; cleaning the parameters from the stack
        
        push dword message2 ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4 * 1
        
        push dword b       ; pushing the parameters on the stack from right to left
		push dword format
		call [scanf]       ; calling the scanf function for reading
		add esp, 4 * 2     ; cleaning the parameters from the stack\
        
        mov eax, dword [a]
        mov edx, 0
        div dword [b] ; EAX = a / b
        mov EBX, k
        mul EBX ; EAX = (a / b) / k
        
        PUSHAD
        
        push dword eax
		push dword format2 
		call [printf]      ; call function for printing
		add esp, 4 * 2       ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
        
        POPAD
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program