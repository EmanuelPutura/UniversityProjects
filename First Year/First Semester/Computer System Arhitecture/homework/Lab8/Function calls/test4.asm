bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        var1 dq 1
        A db 17,-2
        B dw -20345, "x"
        Start2:
        C dd 12345678h
        D db $ - A
        var dd 1
; our code starts here
segment code use32 class=code
    start:
        mov qword [var1], 0
        mov eax, [ebx + ebp] ; DS
        mov eax, [ebp + ebx] ; SS
        mov eax, [ebx + esp] ; SS
        mov eax, [esp + ebx] ; SS
        mov eax, 0
        mov eax, [esp*1 + ebx]
        mov eax, [ebx + esp*1]
        mov eax, [ebx*1 + esp*1]
        mov eax, 12345678h
        mov [var], eax
        mov ebx, [var]
        mov eax, 0
        mov eax, [D]
        and eax, 0
        mov al, [D]
        mov ecx, 50
        mov [var], ecx
        ;mov eip, 50
        mov eax, 0
        times 5 add eax, dword [var]
        mov eax, 50
        sub eax, eax
        mov ebx, 50
        times 1 sub ebx, ebx
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
