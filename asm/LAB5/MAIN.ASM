assume cs:cdseg
cdseg segment 'code'
	org 100h
main:
	; load data segment
	push cs
	pop ds
	
	;main
	;print lab title
	mov dx, offset lab_title
	call putstr
	call clrf
	
	;cycle for string input
	string_input:
		mov cx, 20
		mov si, 0
		string_input_loop:
			;get char
			call getch
			mov dl, al
			call putch
			
			; check if input ended
			cmp al, 13
			je print_string
			cmp al, '*'
			je final
			
			mov buf[si], al
			inc si
		LOOP string_input_loop
	
	
	;print string
	print_string:
		cmp si, 0
		je final
		mov cx, si
		mov si, 0
		print_string_loop:
			mov dl, buf[si] 
			call putch
			inc si
		LOOP print_string_loop
		mov dl, ' '
		call putch
		mov dl, '='
		call putch
		mov dl, ' '
		call putch
		
		mov cx, si
		mov si, 0
		print_string_hex_loop:
			mov dl, buf[si]
			mov let, dl
			call printhex
			
			mov dl, ' '
			call putch
			
			inc si
			
		loop print_string_hex_loop
		call clrf
		
		mov dl, 0ah
		call putch
		
		inc strings_amount
		cmp strings_amount, 10
		jne string_input
		; jmp string_input
	
	
	
	final:
	;quit
	mov al, 0
	mov ah, 4CH
	int 21H
putch proc
	mov ah, 02
	int 21H
	ret
putch endp

putstr proc
	mov ah, 09
	int 21h
	ret
putstr endp

getch proc
	mov ah, 08h
	int 21h
	ret
getch endp

clrf proc
	mov dl, 10
	call putch
	mov dl, 13
	call putch
	ret
clrf endp

clrscr proc
    call clrf
    mov  ah , 0H
    mov  al , 3H
    int  10H
    ret
clrscr endp

printhex proc
	; first digit
	mov al, let
	shr al, 4
	lea bx, hex_table
	xlat
	mov dl, al
	call putch
	
	;second digit
	mov al, let
	and al, 0fh
	xlat 
	mov dl, al
	call putch
	
	;final letter h
	mov dl, 'h'
	call putch
	ret
printhex endp
lab_title db 'Lab 5: strings input$'
hex_table db '0123456789ABCDEF'
buf db 21 dup('_')
let db 'A'
strings_amount db 0
cdseg ends

end main
