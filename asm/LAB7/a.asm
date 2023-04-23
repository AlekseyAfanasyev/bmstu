dtseg segment 'data'
	lab_title db 'Lab 7: hex to bin, bin to hex, horners method$'

	value_error db 'Error!', 0ah, 'Allowed chars: 0123456789ABCDEF', 0ah, 'Aborting$'

	greet_hint db 'Enter hex number in HHHHHHHH format:>$'
	bin_output_hint db 'Bin: $'
	dec_output_hint db 'Dec: $'
	hex_output_hint db 'Hex: $'

	string db 9 dup('_')
	bin_string db 33 dup('_')
	hex_string db 9 dup('_')
	dec_string db 11 dup('0')
	first_dw dw 0
	second_dw dw 0
	num dd 0
	div_result db 0
	dd_buf dd 0
	dw_buf dw 0
	powers_of_10 dd 3B9ACA00h, 05F5E100h, 00989680h, 000F4240h, 000186A0h, 00002710h, 000003E8h, 00000064h, 0000000Ah
dtseg ends

sseg segment 'stack'
	db 400h dup(0)
sseg ends


cdseg segment 'code'
	assume cs:cdseg, ds:dtseg, ss:sseg

start:
	; load data segment
	mov ax, dtseg
	mov ds, ax

	; print lab lab_title
	mov dx, offset lab_title
	call putstr
	call clrf
	call clrf

	; print greet hint
	mov dx, offset greet_hint
	call putstr

	; get string
	mov si, 0
	mov cx, 8 ; 8 - hex number length
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
	
	;write string 
	mov si, 3
	mov cx, 4
	fill_dw1:
		mov dl, string[si]
		call isdigit
		je process_digit1
		jne process_alpha1
		process_digit1:
			sub string[si], '0'
			jmp add_to_dw1
		process_alpha1:
			sub string[si], 'A'
			add string[si], 10
			jmp add_to_dw1
		add_to_dw1:
			; di = power of 16
			mov di, 3
			sub di, si
			
			;load 16^0 to ax
			mov ax, 1
			
			; if power of 16 is 0, skip the rest
			cmp di, 0
			je fill_dw_cycle_end1
			
			; multiply ax (di) times
			mov bx, cx
			mov cx, di
			move_16_power_to_ax1:
				shl ax, 4
			loop move_16_power_to_ax1
			mov cx, bx
		fill_dw_cycle_end1:
			cmp string[si], 0
			je fill_dw_cycle_end_skip_adding1
			mov bx, 0
			mov bl, string[si]
			mov dx, 0
			mul bx
			add first_dw, ax
			
			fill_dw_cycle_end_skip_adding1:
				dec si
	loop fill_dw1
	
	; fill second_dw
	mov si, 3
	mov cx, 4
	fill_dw2:
		mov dl, string[si + 4]
		call isdigit
		je process_digit2
		jne process_alpha2
		process_digit2:
			sub string[si + 4], '0'
			jmp add_to_dw2
		process_alpha2:
			sub string[si + 4], 'A'
			add string[si + 4], 10
			jmp add_to_dw2
		add_to_dw2:
			; di = power of 16
			mov di, 3
			sub di, si
			
			;load 16^0 to ax
			mov ax, 1
			
			; if power of 16 is 0, skip the rest
			cmp di, 0
			je fill_dw_cycle_end2
			
			; multiply ax (di) times
			mov bx, cx
			mov cx, di
			move_16_power_to_ax2:
				shl ax, 4
			loop move_16_power_to_ax2
			mov cx, bx
		fill_dw_cycle_end2:
			cmp string[si + 4], 0
			je fill_dw_cycle_end_skip_adding2
			mov bx, 0
			mov bl, string[si + 4]
			mov dx, 0
			mul bx
			add second_dw, ax
			
			fill_dw_cycle_end_skip_adding2:
				dec si
	loop fill_dw2
	
	; make binary string
	
	;first_dw
	mov cx, 16
	mov di, 15
	
	mov ax, first_dw
	mov dw_buf, ax
		
	make_bin1:
		mov ax, dw_buf
		and ax, 1
		cmp ax, 1
		je add_11
		jne add_01
		add_11:
			mov bin_string[di], '1'
			jmp make_bin_cycle_end1
		add_01:
			mov bin_string[di], '0'
			jmp make_bin_cycle_end1
		make_bin_cycle_end1:
			dec di
			shr dw_buf, 1
	loop make_bin1
	
	
	;second_dw
	mov cx, 16
	mov di, 15
	
	mov ax, second_dw
	mov dw_buf, ax
		
	make_bin2:
		mov ax, dw_buf
		and ax, 1
		cmp ax, 1
		je add_12
		jne add_02
		add_12:
			mov bin_string[di + 16], '1'
			jmp make_bin_cycle_end2
		add_02:
			mov bin_string[di + 16], '0'
			jmp make_bin_cycle_end2
		make_bin_cycle_end2:
			dec di
			shr dw_buf, 1
	loop make_bin2
	
	mov bin_string[32], '$'
	
	; print resulted bin string
	mov dx, offset bin_output_hint
	call putstr
	mov dx, offset bin_string
	call putstr
	call clrf
	
	; fill hex string
	mov cx, 4
	mov si, 3
	mov bx, first_dw
	mov dw_buf, bx
	make_hex1:
		mov bx, dw_buf
		and bx, 0Fh
		cmp bx, 09h
		jle make_hex_process_digit1
		jg make_hex_process_alpha1
		jmp make_hex_cycle_end1
		make_hex_process_alpha1:
			mov hex_string[si], 'A'
			add hex_string[si], bl
			sub hex_string[si], 0Ah
			jmp make_hex_cycle_end1
		make_hex_process_digit1:
			mov hex_string[si], '0'
			add hex_string[si], bl
			jmp make_hex_cycle_end1
		make_hex_cycle_end1:
			shr dw_buf, 4
			dec si
	loop make_hex1
	mov cx, 4
	mov si, 3
	mov bx, second_dw
	mov dw_buf, bx
	make_hex2:
		mov bx, dw_buf
		and bx, 0Fh
		cmp bx, 09h
		jle make_hex_process_digit2
		jg make_hex_process_alpha2
		jmp make_hex_cycle_end2
		make_hex_process_alpha2:
			mov hex_string[si+4], 'A'
			add hex_string[si+4], bl
			sub hex_string[si+4], 0Ah
			jmp make_hex_cycle_end2
		make_hex_process_digit2:
			mov hex_string[si+4], '0'
			add hex_string[si+4], bl
			jmp make_hex_cycle_end2
		make_hex_cycle_end2:
			shr dw_buf, 4
			dec si
	loop make_hex2
	mov hex_string[8], '$'
	
	; print hex string
	mov dx, offset hex_output_hint
	call putstr
	mov dx, offset hex_string
	call putstr
	call clrf
	
	; move first_dw and second_dw to 
	mov bx, first_dw
	mov word ptr num+2, bx
	mov bx, second_dw
	mov word ptr num, bx
	
	mov cx, 9
	mov si, 0
	mov di, 0
	call mov_num_to_buf
	make_dec:
		; call div_dd
		; mov dl, div_result
		; add dl, '0'
		; call putch
		; mov al, div_result
	
		; mov dec_string[si], al
		; add dec_string[si], '0'
		
		; inc si
		; add di, 4
	loop make_dec
	
	mov al, div_result
	mov dec_string[8], al
	add dec_string[8], '0'
	; mov ax, word ptr dd_buf + 2
	mov ax, word ptr dd_buf + 2
	mov dec_string[9], al
	add dec_string[9], '0'
		
		
	mov dec_string[10], '$'
	
	mov dx, offset dec_output_hint
	call putstr
	mov dx, offset dec_string
	call putstr
	call clrf
	
	
	
	call exit
	
;dd_buf - remainder
;div_result - div_result
;делим dd_buf на powers_of_10[di]
mov_num_to_buf proc
	mov bx, word ptr num
	mov word ptr dd_buf, bx
	mov bx, word ptr num+2
	mov word ptr dd_buf+2, bx
mov_num_to_buf endp
div_dd proc
	push ax
	push bx
	mov div_result, 0
	div_loop:
		; check if we still can substract from dd_buf
		mov ax, word ptr dd_buf+2
		mov bx, word ptr powers_of_10[di]+2
		cmp ax, bx
		jl div_loop_end
		mov ax, word ptr dd_buf
		mov bx, word ptr powers_of_10[di]
		cmp ax, bx
		jl div_loop_end
		;substract
		call sub_dd
		inc div_result
		jmp div_loop
			
	div_loop_end:
		pop ax
		pop bx
		ret
	
div_dd endp

;sub powers_of_10[di] from dd_buf
sub_dd proc
	push ax
	push bx
	push dx
	push cx
	mov ax, word ptr dd_buf + 2
	mov bx, word ptr dd_buf
	mov dx, word ptr powers_of_10[di] + 2
	mov cx, word ptr powers_of_10[di] 
	sub_loop:
		;check if we already substracted
		cmp cx, 0
		je roll_powers
		dec cx
		jmp sub_from_dd
		roll_powers:
			cmp dx, 0
			je sub_loop_end
			dec dx
			mov cx, 0FFFFh
			jmp sub_from_dd
		sub_from_dd:
			cmp bx, 0
			je roll_dd
			dec bx
			jmp sub_loop
			roll_dd:
				cmp ax, 0
				je sub_loop_end
				dec ax
				mov bx, 0FFFFh
				jmp sub_loop
	sub_loop_end:
		mov word ptr dd_buf + 2, ax
		mov word ptr dd_buf, bx
		pop ax
		pop bx
		pop dx
		pop cx
		ret

sub_dd endp


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
