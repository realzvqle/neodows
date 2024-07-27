
BITS 16
ORG 0x7C00

_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    call set_video_mode
    mov si, message
    call print_string
    call new_line
    mov si, type
    call print_string
    call new_line
    call new_line
    mov si, instructions
    call print_string
    call new_line
    call new_line

loop:
    call wait_for_key
    call print_char
    jmp loop

set_video_mode:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

wait_for_key:
    mov ah, 0x00
    int 0x16
    ret

print_char:
    mov ah, 0x0E
    int 0x10
    ret
    
print_string:
    lodsb
    cmp al, 0
    je .return 
    mov ah, 0x0E
    int 0x10
    jmp print_string



.return:
    ret    



new_line:
    mov al, 0x0D
    mov ah, 0x0E
    int 0x10
    mov al, 0x0A
    mov ah, 0x0E
    int 0x10
    ret

message db "Neodows Build INDEV (RESET)", 0
type db "NeoLDR Build INDEV", 0

instructions db "Type Some Stuff", 0

times 510-($-$$) db 0
dw 0xAA55
    
    