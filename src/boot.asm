BITS 16
ORG 0x7C00


_start:
    xor ax, ax
    mov ds, ax
    mov es, ax




    mov si, message


print_char:
    lodsb
    cmp al, 0
    je _done
    mov ah, 0x0E
    int 0x10
    jmp print_char
    


_done:
    cli
    hlt

message db 'Neodows Build Reset', 0
times 510-($-$$) db 0
dw 0xAA55
    
    