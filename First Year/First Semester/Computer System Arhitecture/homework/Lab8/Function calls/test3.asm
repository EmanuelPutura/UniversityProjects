bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        v db 2
        const equ 'i'
; our code starts here
segment code use32 class=code
    start:
        mov eax, [10h:v]
        mov eax, [cs:00402000h]
        mov eax, 0
        test_label3:
        mov eax, test_label3
        ;mov bx, ES xlat
        
        mov ebx, const
        mov ax, v + 3 
        test_label2:
        mov eax, 0
        test_label:
        mov eax, $
        mov edx, test_label
        mov ebx, $$
        mov ecx, test_label2    
        ;mov ebx, $$  
        mov eax, [cs:ebx]
        lea ebx, [cs:ebx]
        lea ecx, [fs:ebx]
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
