; program to convert 4-character hex string into binary and decimal
dtseg segment 'data'
	lab_title db 'Lab 7: hex to bin, bin to hex, horners method$'

	value_error db 'Error!', 0ah, 'Allowed chars: 0123456789ABCDEF', 0ah, 'Aborting$'

	greet_hint db 'Enter hex number in HHHH format:>$'
	bin_output_hint db 'Bin: $'
	dec_output_hint db 'Dec: $'
	hex_output_hint db 'Hex: $'

	hex_table db '0123456789ABCDEF'
	string db '____'
	bin_string db 17 dup('_')
	hex_string db 5 dup('_')
	dec_string db 6 dup('0')
	string_dw dw 0
	dw_buf dw 0
	powers_of_10 dw 10000, 1000, 100, 10, 1
dtseg ends


cdseg segment 'code'
	assume cs:cdseg, ds:dtseg

start:
	; load data segment
	mov ax, dtseg
	mov ds, ax

	;print lab lab_title
	mov dx, offset lab_title
	call putstr
	call clrf
	call clrf

	;print greet hint
	mov dx, offset greet_hint
	call putstr

	;get string
	mov si, 0
	mov cx, 4
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

	mov si, 3
	mov cx, 4
	fill_dw:
		mov dl, string[si]
		call isdigit
		je process_digit
		jne process_alpha
		process_digit:
			sub string[si], '0'
			jmp add_to_dw
		process_alpha:
			sub string[si], 'A'
			add string[si], 10
			jmp add_to_dw
		add_to_dw:
			; di = power of 16
			mov di, 3
			sub di, si
			
			;load 16^0 to ax
			mov ax, 1
			
			; if power of 16 is 0, skip the rest
			cmp di, 0
			je fill_dw_cycle_end
			
			; multiply ax (di) times
			mov bx, cx
			mov cx, di
			move_16_power_to_ax:
				shl ax, 4
			loop move_16_power_to_ax
			mov cx, bx
		fill_dw_cycle_end:
			cmp string[si], 0
			je fill_dw_cycle_end_skip_adding
			mov bx, 0
			mov bl, string[si]
			mov dx, 0
			mul bx
			add string_dw, ax
			
			fill_dw_cycle_end_skip_adding:
				dec si
	loop fill_dw
	
	mov cx, 16
	mov di, 15
	
	mov ax, string_dw
	mov dw_buf, ax
		
	make_bin:
		mov ax, dw_buf
		and ax, 1
		cmp ax, 1
		je add_1
		jne add_0
		add_1:
			mov bin_string[di], '1'
			jmp make_bin_cycle_end
		add_0:
			mov bin_string[di], '0'
			jmp make_bin_cycle_end
		make_bin_cycle_end:
			dec di
			shr dw_buf, 1
	loop make_bin
	mov bin_string[16], '$'
	
	mov dx, offset bin_output_hint
	call putstr
	mov dx, offset bin_string
	call putstr
	call clrf
	
	mov cx, 4
	mov si, 3
	mov bx, string_dw
	mov dw_buf, bx
	make_hex:
		mov bx, dw_buf
		and bx, 0Fh
		cmp bx, 09h
		jle make_hex_process_digit
		jg make_hex_process_alpha
		jmp make_hex_cycle_end
		make_hex_process_alpha:
			mov hex_string[si], 'A'
			add hex_string[si], bl
			sub hex_string[si], 0Ah
			jmp make_hex_cycle_end
		make_hex_process_digit:
			mov hex_string[si], '0'
			add hex_string[si], bl
			jmp make_hex_cycle_end
		make_hex_cycle_end:
			shr dw_buf, 4
			dec si
	loop make_hex
	mov hex_string[4], '$'
	
	mov dx, offset hex_output_hint
	call putstr
	mov dx, offset hex_string
	call putstr
	call clrf

	mov cx, 5
	mov si, 0
	mov bx, string_dw
	mov dw_buf, bx
	mov di, 0
	make_dec:
		;bl = power of 10
		mov bx, 0
		mov bx, powers_of_10[di]
		mov ax, dw_buf
		mov dx, 0
		div bx
		add dec_string[si], al
		mov dw_buf, dx
		inc si
		add di, 2
	loop make_dec
	mov dec_string[5], '$'

	mov dx, offset dec_output_hint
	call putstr
	mov dx, offset dec_string
	call putstr
	call clrf


	
	call exit



exit proc
	mov al, 0
	mov ah, 4CH
	int 21H
exit endp

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
