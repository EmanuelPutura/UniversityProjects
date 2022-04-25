%ifdef COMMENT
    8. A list of doublewords is given. Obtain the list made out of the low bytes of the high words of each doubleword from the given list with the property that these bytes are palindromes in base 10.
    Example:
        Given the string of doublewords:
            S DD 12345678h, 1A2C3C4Dh, 98FCDC76h
        obtain the string of bytes:
            D DB 2Ch, FCh
%endif

bits 32 

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
        S dd 12345678h, 1A2C3C4Dh, 98FCDC76h ; the given string
        L equ ($ - S) / 4 ; the length of S
        T times L db 0 ; a temporary string for every current number's digits 
        D resb L; we save in memory enough space for the D string
        
segment code use32 class=code
    start:
        mov ESI, S ; the source string is S
        mov EDI, D ; the destination string is DB
        mov ECX, L ; we will parse the elements of S in a loop with L iterators
        
        CLD ; parse the string from left to right (DF = 0)
        ; --------------------------------------------
        for_every_element_in_S:
            lodsw ; in AX we will have the low word of the of the current doubleword of the S string
            lodsb ; in AL we will have the low byte of the high word of the of the current doubleword of the S string
            
            ; first we have to find the number of digits of the current found number
            mov BL, AL ; we save a copy of the number in BL
            cbw ; we convert the byte to word (signed)
            
            mov DH, 0 ; we save in DH the number of digits of the current number
            mov DL, 10 ; for the division by 10
        ; --------------------------------------------
            
            ; --------------------------------------------
            for_every_digit_in_the_current_no:
                inc DH ; increment the number of digits
                div DL ; AL <- AX / DL, AH <- AX % DL
                ; we are interested in the quotient of the division
                
                mov EDI, T ; we temporarily move the address of T into EDI
                STOSB ; we store AL into the byte from the address <ES:EDI>, so basically we store AL into T
                
                cbw ; we need only the number from AL. We need to convert it to AX
                cmp AL, 0
                jnz for_every_digit_in_the_current_no ; if AL != 0 (so if the quotient is != 0), we continue
            ; --------------------------------------------
            
            ; after the loop we have DH = the number of digits of the current number
            mov AL, BL ; we restore the initial value of the current number
            mov BH, DH ; we save a copy of DH
            mov AL, DH
            cbw ; signed conversion from AL to AX
            mov DL, 2 ; we save this constant here in order to use it for the division
            div DL ; AL <- AX / DL = AX / 2
            mov DH, AL ; DH <- AX / 2 = DH / 2
            ; basically DH is the number of steps in the following loop
            mov BL, DH ; we save in BL the number of digits of the current number / 2
            ; also note that BH is [BL] * 2
            
            ; --------------------------------------------
            
            mov DL, 0 ; the index in the following loop
            check_if_palindrome_loop:
                mov DH, BH ; DH - the number of iterations in this loop
                ; DL = the current index
                sub DH, DL  
                ; we have now to compare T[i] and T[DH - i - 1]
                mov AL, [T + DH - DL - 1]
                mov EDI, T
                
                CMPSB
                
                
                inc DL
                dec BL
                cmp BL, 0
                jz for_every_element_in_S
            ; --------------------------------------------
        loop for_every_element_in_S
        ; --------------------------------------------
        
        push    dword 0
        call    [exit]
