%ifdef COMMENT
    8. A text file is given. Read the content of the file, determine the uppercase letter with the highest frequency and display the letter along with its frequency on the screen. The name of text file is defined in the data segment.
%endif

bits 32

global start        

extern exit, fread, printf, fopen, fclose
import exit msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
        file_name db "file8.txt", 0 ; the name of the file
        file_descriptor dd -1       ; the file descriptor returned by fopen in EAX
        access_mode db "r", 0       ; the file access mode
        len equ 100                 ; we read 100 characters from the file at a time
        text times (len + 1) db 0   ; the text read from the file at a time
        r db 0xFF
        frequency_array times ("z" - "a" + 1) dd 0 ; the frequency array for the characters
        format db "The uppercase letter with the highest frequency is %c, having the frequency %u", 0
segment code use32 class=code
    start:
        ; we call fopen() to open the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode
        push dword file_name
        call [fopen]
        add ESP, 4 * 2 ; clean-up the stack
        
        cmp EAX, 0
        je open_error
        
        mov [file_descriptor], EAX ; we save the file descriptor
        
        
        read_from_file:
            ; we read the text from file using fread()
            ; after the fread() call, EAX will contain the number of chars we have read 
            ; eax = fread(text, 1, len, file_descriptor)
            push dword [file_descriptor]
            push dword len
            push dword 1
            push dword text
            call [fread]
            add ESP, 4 * 4 ; clean-up the stack
            
            cmp EAX, 0
            je reading_done
                
            mov EBX, EAX   
            mov ESI, text ; the source array
            text_loop:
                mov EAX, 0
                LODSB ; load the current byte character from <DS:ESI> into AL
                cmp AL, 'A'
                jl continue ; if the current character is not uppercase
                cmp AL, 'Z' ; if the current character is not uppercase
                jg continue
                
                ; now we are sure that the actual character (stored in AL) is uppercase
                sub EAX, 'A'
                add dword [EAX*4 + frequency_array], 1 ; offset specification formula, increase the frequency of the character
                
                continue:
                
                sub EBX, 1
                cmp EBX, 0
                je read_from_file
            jmp text_loop
        jmp read_from_file
        
        reading_done:
        
        mov ECX, "z" - "a" + 1 ; the length of the frequency array
        mov EBX, 0 ; the max frequency
        mov ESI, frequency_array
        mov EDX, 0 ; the uppercase character with the highest frequency
        
        find_max_frequency:
            LODSD ; EAX <- the current frequency
            CMP EBX, EAX
            jg continue_searching
            
            mov EBX, EAX
            mov EDX, "Z"
            sub EDX, ECX
            add EDX, 1
            
            continue_searching:
        loop find_max_frequency
        
        push dword EBX ; the max frequency
        push dword EDX ; the uppercase character with the max frequency
        push format
        call [printf]
        add esp, 4 * 3 ; clean-up the stack
        
        ; we call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add ESP, 4 * 1 ; clean-up the stack
        
        open_error:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
