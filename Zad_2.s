		AREA	MAIN_CODE, CODE, READONLY
		GET		LPC213x.s
		
		ENTRY
		
__main
__use_two_region_memory
		EXPORT			__main
		EXPORT			__use_two_region_memory
	
	
	LDR R0, =100
	LDR R1, =2400
	MUL R1, R0, R1
main_loop
		SUBS R1, R1, #1
		CMP R1, #0
		BNE main_loop
		NOP
		END