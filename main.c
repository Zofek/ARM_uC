#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

#define S0_bm 0x00000010
#define S1_bm 0x00000040
#define S2_bm 0x00000020
#define S3_bm 0x00000080

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum Direction {RIGHT, LEFT};

unsigned char ucCounter;

void Delay(unsigned int uiMiliseconds){
	
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (uiMiliseconds * 5452); uiCounter++){}
}

void LedInit(){
	
	IO1DIR = (IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm));
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){

	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	
	switch(ucLedIndeks){
		case 0:
			IO1SET = LED0_bm;
		break;
		case 1: 
			IO1SET = LED1_bm;
		break;
		case 2: 
			IO1SET = LED2_bm; 
		break;
		case 3: 
			IO1SET = LED3_bm; 
		break;
		default:
		break;
	}
}

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

void LedStep(enum Direction LedDirection){
	
	static unsigned int uiDirection;
	
	if (LedDirection == RIGHT){
			
		uiDirection = (uiDirection - 1) % 4;
	
		LedOn(uiDirection);}
	
	else if (LedDirection == LEFT){
			
		uiDirection = (uiDirection + 1) % 4;
	
		LedOn(uiDirection);}
}

void LedStepLeft(void){
	LedStep(LEFT);
}

void LedStepRight(void){
	LedStep(RIGHT);
}

int main(){
		
	LedInit();
	
		while(1){
			switch(eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
			break;
			case BUTTON_2:
				LedStepLeft();
			break;
			default:
				break;
			}
		}
}
