#include "timer_interrupts.h"
#include "keyboard.h"
#include "servo.h"

int main ()
{
    unsigned int iMainLoopCtr;

    KeyboardInit();
    DetectorInit();
    ServoInit(4);

    while(1)
    {
        if (BUTTON_0 == eKeyboardRead())
        {
            ServoCallib();
        }
        if (BUTTON_1 == eKeyboardRead())
        {
            ServoGoTo(12);
        }
        if (BUTTON_2 == eKeyboardRead())
        {
            ServoGoTo(24);
        }
        iMainLoopCtr++;
    }
}
