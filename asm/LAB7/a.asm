dtseg segment 'data'
	lab_title db 'Lab 7: hex to bin, bin to hex, horners method$'
	value_error db 'Error!', 0ah, 'Allowed chars: 0123456789ABCDEF', 0ah, 'Aborting$'

	string db 9 dup('_')
	buf_db db 0

	number dd 0
	buf_dd dd 0

	powers_of_16 dd 1h, 10h, 100h, 1000h, 10000h, 100000h, 1000000h, 10000000h
dtseg ends

stseg segment 'stack'
	buf db 1024 dup(' ')
stseg ends


cdseg segment 'code'
	assume cs:cdseg, ds:dtseg, ss:stseg

start:
	; load data segment
	mov ax, dtseg
	mov ds, ax

	; print lab title
	mov dx, offset lab_title
	call putstr
	call clrf
	call clrf

	; input string
	mov si, 0
	mov cx, 8
	string_check:
		call getch
		mov string[si], al
		mov dl, string[si]
		call isdigitalpha
		jne show_value_error
		jmp string_check_end
		show_value_error:
			call clrf
			mov dx, offset value_error
			call putstr
			call clrf
			call exit
		string_check_end:
			inc si
	loop string_check
	call clrf
	mov string[8], '$'


	; exit
	call exit



exit proc
	mov al, 0
	mov ah, 4CH
	int 21H
exit endp

add_dd proc
add_dd endp

isdigitalpha proc
	call isdigit
	jne check_isaplha
	je digitalpha
	check_isaplha:
		call isalpha
		jne not_digitalpha
		je digitalpha
	not_digitalpha:
		cmp dl, '0'
		ret
	digitalpha:
		cmp dl, dl
		ret
isdigitalpha endp

isdigit proc
	cmp dl, '0'
	jl not_digit

	cmp dl, '9'
	jg not_digit

	jmp digit
	not_digit:
		cmp dl, '0'
		ret
	digit:
		cmp dl, dl
		ret
isdigit endp

isalpha proc
	cmp dl, 'A'
	jl not_alpha

	cmp dl, 'F'
	jg not_alpha

	jmp alpha
	not_alpha:
		cmp dl, 'A'
		ret
	alpha:
		cmp dl, dl
		ret
isalpha endp

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
	mov ah, 01h
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
cdseg ends

end start
