[BITS 16]
[ORG 0x7C00]

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
    mov si, kernel_load
    call print_string
    call load_kernel
    mov si, a20_load
    call print_string
    call load_a20
    mov si, protected_load
    call print_string
    call switch_to_protected_mode
    mov si, kernel_start
    call print_string
    jmp 0x1000:0x0000        

loop:
    hlt
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
    je _return 
    mov ah, 0x0E
    int 0x10
    jmp print_string

_return:
    ret

new_line:
    mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov ah, 0x0E
    mov al, 0x0A
    int 0x10
    ret


load_kernel:
    mov ah, 0x02    
    mov al, 1        
    mov ch, 0        
    mov cl, 2        
    mov dh, 0       
    mov dl, 0x80     
    mov bx, 0x1000   
    int 0x13         
    jc kernel_fail_load
    ret

load_a20:
    mov al, 0x01
    out 0x92, al
    ret

switch_to_protected_mode:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_protected_mode

[BITS 32]
init_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    jmp 0x10:0x1000

kernel_fail_load:
    mov si, kernel_error
    call print_string
    call new_line
    call new_line
    jmp $

gdt_start:
    dq 0x0000000000000000   ; Null descriptor
    dq 0x00CF9A000000FFFF   ; Code segment descriptor
    dq 0x00CF92000000FFFF   ; Data segment descriptor
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

message db "Neodows Build INDEV (RESET)", 0
type db "NeoLDR Build INDEV", 0
kernel_error db "Error loading Neodows kernel", 0
a20_load db "Started a20", 0
kernel_load db "Loaded Kernel", 0
protected_load db "Switched to Protected (32bit) Mode", 0
kernel_start db "Starting Kernel", 0



instructions db "Type Some Stuff", 0

times 510-($-$$) db 0
dw 0xAA55
