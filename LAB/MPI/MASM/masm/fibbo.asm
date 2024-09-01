data segment
 num db 00h
 num2 db 01h
 fib db 00h dup(?)
data ends

code segment
 assume cs:code,ds:data
 start:mov ax,data
       mov ds,ax

      mov al,num
      mov ah,num2
      mov cx,0005h
      mov bl,00h
      lea di,fib
 l1:  add al,ah
      mov [di],al
      mov bl,al
      inc di
      mov al,ah
      mov ah,bl
      loop l1
      mov ah,4ch
      int 21h
code ends
end start