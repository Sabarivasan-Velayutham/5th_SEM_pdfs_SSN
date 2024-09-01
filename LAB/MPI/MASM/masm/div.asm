assume cs:code,ds:data
data segment
     count equ 08h
     array db 08h dup(?)
data ends

code segment
start:  mov ax,data
     mov ds,ax
     mov cl,count
     dec cl
l1:  lea si,array
     mov ch,count
     dec ch
l3:  mov al,[si]
     cmp al,[si+1]
     jc l2
     mov ah,[si+1]
     xchg al,ah
     mov [si],al
     mov [si+1],ah
l2:  inc si
     dec ch
     jnz l3
     dec cl
     jnz l1 
     mov ah,4ch
     int 21h
code ends
end start

     