#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat(void)
{

    enum LedState {STOP, TO_RIGHT, TO_LEFT};
    static enum LedState eLedState = STOP;

    switch(eLedState)
    {
    case STOP:
    {
        if (BUTTON_2 == eKeyboardRead())
        {
            eLedState = TO_RIGHT;
        }
        else if (BUTTON_0 == eKeyboardRead())
        {
            eLedState = TO_LEFT;
        }
        else
        {
            eLedState = STOP;
        }
    }
    break;
    case TO_RIGHT:
    {
        if (BUTTON_1 == eKeyboardRead())
        {
            eLedState = STOP;
        }
        else
        {
            eLedState = TO_RIGHT;
            LedStepRight();
        }
    }
    break;
    case TO_LEFT:
    {
        if (BUTTON_1 == eKeyboardRead())
        {
            eLedState = STOP;
        }
        else
        {
            eLedState = TO_LEFT;
            LedStepLeft();
        }
    }
    break;
    default:
        break;
    }
}

int main ()
{

    unsigned int iMainLoopCtr;
    LedInit();
    KeyboardInit();
    Timer0Interrupts_Init(20000,&Automat);

    while(1)
    {
			iMainLoopCtr++;
    }
}
