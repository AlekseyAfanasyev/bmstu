dtseg segment 'data'
	lab_title db 'Lab 6: command line arguments$'
	name_message db 'Name:$'
	school_message db 'School:$'
	no_arguments_error db 'you should provide at least 2 arguments$'
	hex_table db '0123456789ABCDEF'
	let db '_'
dtseg ends


cdseg segment 'code'
	assume cs:cdseg, ds:dtseg

start:
	; load data segment
	mov ax, dtseg
	mov ds, ax



	;main
	;print lab title
	mov dx, offset lab_title
	call putstr; 	school db 4 dup('_')
	call clrf

	; get command line arguments amount
	mov cl, es:80h

	; check if command line argumename_messagents amount is not zero
	cmp cx, 0
	je no_arguments

	mov bx, 80h
	get_arguments_cycle:
		; go to next cell in psp
		inc bx
		; get cur cell
		mov dl, es:bx

		;check if command defined
		cmp dl, '/'
		je set_command

		cmp let, 'N'
		je name_input

		cmp let, 'S'
		je school_input

		jmp get_arguments_cycle_end



		name_input:
			call putch
			jmp get_arguments_cycle_end

		school_input:
			call putch
			jmp get_arguments_cycle_end


		set_command:
			mov dl, 0ah
			call putch

			inc bx
			mov dl, es:bx
			mov let, dl
			mov si, 0

			cmp dl, 'N'
			je name_message_output

			cmp dl, 'S'
			je school_message_output

			jmp get_arguments_cycle_end


			name_message_output:
				mov dx, offset name_message
				call putstr
				call clrf
				jmp get_arguments_cycle_end
			school_message_output:
				mov dx, offset school_message
				call putstr
				call clrf
				jmp get_arguments_cycle_end

		get_arguments_cycle_end:

	loop get_arguments_cycle
	jmp final



	no_arguments:
	mov dx, offset no_arguments_error
	call putstr
	call clrf
	jmp final
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
cdseg ends

end start
