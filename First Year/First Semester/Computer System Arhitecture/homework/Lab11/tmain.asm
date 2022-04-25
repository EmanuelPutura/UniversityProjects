bits 32

global start        

extern exit, tprint
import exit msvcrt.dll

segment data use32 class=data
        
segment code use32 class=code
    start:
        mov eax, 10
        call tprint
        
        push    dword 0
        call    [exit]
