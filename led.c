#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16) //0x0010000
#define LED1_bm (1<<17) //0x0020000
#define LED2_bm (1<<18) //0x0040000
#define LED3_bm (1<<19) //0x0080000

enum Direction {RIGHT, LEFT};

unsigned char ucCounter;

void LedInit()
{
    IO1DIR = (IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm)); //0x00F0000
    IO1SET = LED0_bm;
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

    if (LedDirection == RIGHT)
        suiDirection++;

    else if (LedDirection == LEFT)
        suiDirection--;

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

