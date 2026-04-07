section .text
global outw
outw:
    mov dx, [esp + 4] ; port
    mov ax, [esp + 8] ; value
    out dx, ax
    ret
