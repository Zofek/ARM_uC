#include "keyboard.h"
#include "led.h"

enum LedState {STOP, TO_RIGHT, TO_LEFT};
enum LedState eLedState = STOP;

unsigned char ucShiftCounter;

void Delay(unsigned int uiMiliseconds)
{
    unsigned int uiCounter;

    for(uiCounter = 0; uiCounter < (uiMiliseconds * 5452); uiCounter++) {}
}

int main()
{

    LedInit();
    KeyboardInit();

    while(1)
    {

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
        Delay(100);
    }
}
