		AREA	MAIN_CODE, CODE, READONLY
		GET		LPC213x.s
		
		ENTRY
		
__main
__use_two_region_memory
		EXPORT			__main
		EXPORT			__use_two_region_memory
	
	LDR R0, =1000
main_loop
		SUBS R0, R0, 1
		B main_loop

		END