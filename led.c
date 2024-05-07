#include <LPC21xx.H>
#include "led.h"

#define LED0_bm 1<<16 //0x00010000
#define LED1_bm 1<<17 //0x00020000
#define LED2_bm 1<<18 //0x00040000
#define LED3_bm 1<<19 
#define LED4_bm 1<<20
#define LED5_bm 1<<21
#define LED6_bm	1<<22
#define LED7_bm	1<<23

enum Direction {RIGHT, LEFT};

unsigned char ucCounter;

void LedInit()
{
	IO1DIR=IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm|LED4_bm|LED5_bm|LED6_bm|LED7_bm);
	IO1SET= LED0_bm;
}

void Led_ShowByte(unsigned char ucByte)
{
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm|LED4_bm|LED5_bm|LED6_bm|LED7_bm;
	IO1SET = ucByte << 16;
}

void LedOn(unsigned char ucLedIndeks)
{
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);

    switch(ucLedIndeks)
    {
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

void LedStep(enum Direction LedDirection)
{
    static unsigned int suiDirection;

    if (LedDirection == RIGHT){
        suiDirection--;
		}
    else if (LedDirection == LEFT){
        suiDirection++;
		}
    suiDirection = suiDirection%4;
    LedOn(suiDirection);
}

void LedStepLeft(void)
{
    LedStep(LEFT);
}

void LedStepRight(void)
{
    LedStep(RIGHT);
}
