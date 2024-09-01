assume cs:code,ds:data
data segment 
hex db 19h
bcd db 00h
data ends 

code segment
start:mov ax,data
mov ds,ax

mov al,00h
mov bl,hex
labl:cmp bl,00h
jz skip
add al,01h
daa
dec bl
jmp labl
skip: mov bcd,al

mov ah,4ch
int 21h 
code ends 

end start