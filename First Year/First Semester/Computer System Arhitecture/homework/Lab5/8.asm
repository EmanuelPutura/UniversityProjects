%ifdef COMMENT
    8. A character string S is given. Obtain the string D that contains all capital letters of the string S.
     Example:
        S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
        D: 'A', 'B', 'M'
%endif

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        S db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M' ; declaration of the character string S
        L equ $ - S ; the length of s
        D times L db 0
; our code starts here
segment code use32 class=code
    start:
        mov ECX, L ; we save the length of the string in the extended counter register (ECX) 
        mov ESI, 0 ; the value from the extended source index register will be the index in the string S
        mov EDI, 0 ; the value from the extended destination index register will be the index in the string D
        
        jecxz endFor ; in case that the value from ECX is 0
        forLoop:
            mov AL, [S + ESI] ; we move in AL the current character from the string
            
            mov BL, 'A'
            sub BL, AL
            cmp BL, 0
            jg finalFor ; if 'A' - AL > 0 (<=> 'A' > AL), we jump over all the remaining instructions in the loop (excepting the increment of ESI)
            
            mov BL, 'Z'
            sub BL, AL
            cmp BL, 0
            jl finalFor ; if 'Z' - AL < 0 (<=> 'Z' < AL), we jump over all the remaining instructions in the loop (excepting the increment of ESI)
            ; basically now we have checked if 'A' <= current character <= 'Z', so we have checked if the current character is a capital letter
            
            mov [D + EDI], AL ; we move the current character, which is a capital letter, in the string D 
            inc EDI ; incrementing the index in the string D
            
            finalFor:
            inc ESI
        loop forLoop
        endFor: ; the end of the program
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
