;В программе может быть явно объявлено без явных сегментов (DATEи Stack ):
MYCODE SEGMENT 'CODE'   ;Сегмент кода:НАЧАЛО
       ORG 100h  ;Область PSP для СОМ программ
ASSUME CS:MYCODE ;Директива Указание компилятору – всегда первая в сегменте кода
;Начало Сегмента кода:
MAIN :   ;Точка входа 1-й байт после PSP 
msg1 db 'Для завершения программы нажмите любую клавишу:$'
LET DB 'r'
    PUSH CS
    POP   DS 
    MOV DL , LET
    CALL putch
putch proc
	mov ah, 02
	int 21H
	ret
putch endp
main end
;Данные в сегменте кода:
MYCODE ENDS ;Сегмент кода:КОНЕЦ
