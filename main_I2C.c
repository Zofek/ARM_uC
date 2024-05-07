#include "i2c.h"
#include "timer.h"
#include <LPC21xx.H>

#define LED0_bm (1<<16) //0x00010000
#define LED1_bm (1<<17) //0x00020000
#define LED2_bm (1<<18) //0x00040000
#define LED3_bm (1<<19) //0x00080000
#define LED4_bm (1<<20)
#define LED5_bm (1<<21)
#define LED6_bm (1<<22) 
#define LED7_bm (1<<23) 

unsigned char LedInd = 0;
	
int main(){

	InitTimer0();
	I2C_Init();
	IO1DIR = (IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm | LED4_bm | LED5_bm | LED6_bm | LED7_bm));
	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm | LED4_bm | LED5_bm | LED6_bm | LED7_bm);
	
	while(1){
		
		PCF8574_Write(LedInd++);	
		WaitOnTimer0(150000);
	}
}
