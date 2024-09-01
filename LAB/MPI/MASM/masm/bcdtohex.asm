assume cs:code,ds:data
data segment 
bcd db 25h
hex db 00h
data ends 

code segment
start:mov ax,data
mov ds,ax
mov al,bcd 
mov bl,bcd

and bl,0Fh

and al,0F0h
mov cl,04h
ror al,cl
mov dl,0Ah
mul dl
add al,bl
mov hex,al
mov ah,4ch
int 21h 


code ends 

end start