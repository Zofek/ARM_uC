#include <LPC21xx.H>
#include "keyboard.h"

#define S0_bm (1<<4) //0x00000010
#define S1_bm (1<<6) //0x00000040
#define S2_bm (1<<5) //0x00000020
#define S3_bm (1<<7) //0x00000080

enum KeyboardState eKeyboardRead(void)
{
    if (0 == (IO0PIN & S0_bm))
        return BUTTON_0;
    else if (0 == (IO0PIN & S1_bm))   //0x00000010
        return BUTTON_1;
    else if (0 == (IO0PIN & S2_bm)) //0x00000040
        return BUTTON_2;
    else if (0 == (IO0PIN & S3_bm))
        return BUTTON_3;
    else
        return RELEASED;
}

void KeyboardInit()
{
    IO0DIR = (~(S0_bm | S1_bm | S2_bm | S3_bm)) & IO0DIR;
}
