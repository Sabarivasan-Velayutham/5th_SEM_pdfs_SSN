;Program for multpling 2, 8 bit numbers

assume cs:code,ds:data
data segment 
	opr1 db 03h
    opr2 db 05h  
    result dw 00h
data ends
code segment
        org 0100h
start:  mov ax,data
        mov ds,ax
        mov al,opr1
        mov bl,opr2
	    mul bl
 		mov result,ax
        mov ah,4ch
        int 21h
	  code ends  
end start