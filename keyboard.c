#include <LPC21xx.H>
#include "keyboard.h"

#define S0_bm (1<<4)
#define S1_bm (1<<6)
#define S2_bm (1<<5)
#define S3_bm (1<<7) 

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

int eKeyboardRead(){
	if (0 == (IO0PIN & S0_bm))
		return BUTTON_0;
	else if (0 == (IO0PIN & S1_bm))  
		return BUTTON_1;
	else if (0 == (IO0PIN & S2_bm))
		return BUTTON_2;
	else if (0 == (IO0PIN & S3_bm))
		return BUTTON_3;
	else
		return RELEASED;
}

void KeyboardInit(){
	
	IO0DIR = (~(S0_bm | S1_bm | S2_bm | S3_bm)) & IO0DIR;
}
