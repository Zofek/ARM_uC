		AREA	MAIN_CODE, CODE, READONLY
		GET		LPC213x.s
		
		ENTRY
		
__main
__use_two_region_memory
		EXPORT			__main
		EXPORT			__use_two_region_memory

	LDR R0, =1000
main_loop
	BL delay_in_ms
	NOP
	
delay_in_ms
	LDR R1, =2400
	MUL R1, R0, R1
loop_ms
	SUBS R1, R1, #1
	CMP R1, #0
	BNE loop_ms
	BX LR

	END
	
