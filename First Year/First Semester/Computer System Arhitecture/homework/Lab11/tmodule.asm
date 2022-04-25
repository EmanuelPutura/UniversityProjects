bits 32

extern printf
import printf msvcrt.dll

segment data use32 class=data
        format db "%d", 10, 0
segment code use32 class=code
    global tprint
    tprint:
        push eax
        push format
        call [printf]
        add esp, 4 * 2
        ret