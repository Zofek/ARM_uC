		AREA	MAIN_CODE, CODE, READONLY
		GET		LPC213x.s
		
		ENTRY
		
__main
__use_two_region_memory
		EXPORT			__main
		EXPORT			__use_two_region_memory

CURRENT_DIGIT RN R12
	LDR CURRENT_DIGIT, =0

;Ustawienie portów 4-7 na wyjsciowe
	MOV R2, #(15<<4)
	LDR R3, =IO0DIR
	STR R2, [R3]
	
;ustawienie wyswietlaczy na wyjsciowe
	MOV R4, #0x000F0000
	LDR R5, =IO0DIR
	STR R4, [R5]
	
;ustawienie segmentow na wyjsciowe
	MOV R4, #0x00FF0000
	LDR R5, =IO1DIR
	STR R4, [R5];
	
; zalaczenie liczby
	MOV R4, #0x00070000
	LDR R5, =IO1PIN
	STR R4, [R5]
	
;Ustawienie czasu opóznienia [ms]
	LDR R0, =1000
main_loop
	MOV R4, #0x00080000
	LSR R4, R12
	
	LDR R5, =IO0PIN
	STR R4, [R5]
	
	ADD CURRENT_DIGIT, #1
	CMP CURRENT_DIGIT, #4
	EORCS CURRENT_DIGIT, CURRENT_DIGIT, #4
	BL delay_in_ms
	
	B main_loop
	
delay_in_ms
	LDR R1, =2400
	MUL R1, R0, R1
loop_ms
	SUBS R1, R1, #1
	CMP R1, #0
	BNE loop_ms
	BX LR

	END