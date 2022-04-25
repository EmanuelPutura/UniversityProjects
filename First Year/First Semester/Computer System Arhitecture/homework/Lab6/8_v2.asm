%ifdef COMMENT
    8. A list of doublewords is given. Obtain the list made out of the low bytes of the high words of each doubleword from the given list with the property that these bytes are palindromes in base 10.
    Example:
        Given the string of doublewords:
            S DD 1A2C3C4Dh, 12345678h, 98FCDC76h
        obtain the string of bytes:
            D DB 2Ch, FCh
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
        S DD 1A2C3C4Dh, 12345678h, 98FCDC76h
        L equ ($ - S) / 4 ; the length of the S array
        D resb L ; D array has at most L elements
        TEN db 10 ; a byte with the value = 10
        NR dd 0 ; we will need this for Subproblem 2
        
; our code starts here
segment code use32 class=code
    start:
        ; 1. Solution for the problem: we first isolate the byte we are interested in and save it.
        ; 2. Then, we have to generate the number formed by using the same digits as the one already saved, but in reverse order.
        ; 3. If the two numbers are equal, then the current number is a palindrome.
        
        ; ------------- Subproblem 1 -------------
        mov ECX, L ; we will parse the elements of S in a loop with L iterators
        mov ESI, S ; the source string is Solution
        mov EDI, D
        
        for_each_element_in_S:
            mov EAX, 0
            mov [NR], EAX
            CLD ; DF = 0 (parse the string from left to right)
            lodsw ; load in AX the word from the address <DS:ESI> (the low word of the current doubleword)
            ; lodsb ; load in AL the byte from the address <DS:ESI> (the low byte of the high word of the current doubleword)
            
            lodsw
            cbw
            
            
            ; ------------- Subproblem 2 -------------
            ; the byte we are interested in is currently stored in AL
            ; we know that the number we want to generate will be at most a doubleword: if a number has at most 3 digits, we
            ; know that the number we generate from it has the same number of digits, so at most 3 digits. So the generated number
            ; can always be stored in a doubleword.
            
            mov BL, AL ; we save the value of AL in BL
            
            for_each_digit_of_the_current_no:
                mov EAX, [NR]
                mov EDX, 10
                imul EDX ; EDX:EAX <- EAX * EDX = NR * 10
                
                ; we are interested only in EAX bc the nr will always be at most a doubleword
                mov [NR], EAX
                
                mov AL, BL
                cbw
                idiv byte [TEN] ; AL <- AX / 10, AH <- AX % 10 (the last digit of the no)
                mov BL, AL 
                mov AL, AH
                cbw
                cwde
                add dword [NR], EAX
                
                cmp BL, 0
                jnz for_each_digit_of_the_current_no
            
            mov EAX, [NR]
            dec ESI
            dec ESI
            mov BL, [ESI]
            cmp AL, [ESI]
            jnz final
            STOSB
        final:
        inc ESI
        inc ESI
        loop for_each_element_in_S
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
