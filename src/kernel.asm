[BITS 32]
section .text
global _start

_start:
    pushfd
    pop eax

    test eax, 0x00010000    
    jz real_mode            

    mov ah, 0x0E
    mov al, 'P'
    int 0x10         
    jmp done

real_mode:
    mov ah, 0x0E
    mov al, 'A'
    int 0x10       

done:
    hlt
    jmp $
