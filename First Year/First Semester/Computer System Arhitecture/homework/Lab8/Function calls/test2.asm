bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        a db 10
; our code starts here
segment code use32 class=code
    start:
        test_label2:
        
        ;jmp [test_label2]
        
        ;mov edx, test_label2
        ;mov eax, [cs:edx]
        ;mov ebx, [ds:edx]
        ;mov ecx, cs:edx
    
        mov eax, 2
        test_label:
        mov eax, 0
        ;mov eax, test_label
        ;mov ebx, [test_label]
        
        ;jmp cs:eax
        ;mov eax, [cs:eax]
        
        ;jmp [ds:test_label]
        
        ;mov eax, [cs:eax]
        ;mov eax, [ds:eax]
        
        ;jmp [cs:eax]
        mov eax, test_label
        jmp [test_label]
        jmp test_label
        mov eax, [cs:ebx]
        
        mov [a], eax
        mov eax, [eax + ebp]
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
