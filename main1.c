#include "keyboard.h"
#include "led.h"

enum LedState {STOP, TO_RIGHT, TO_LEFT, FLASH};
enum LedState eLedState = STOP;

unsigned char ucBlinkOffCounter;
unsigned char ucBlinkOnCounter;

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
            else if (BUTTON_3 == eKeyboardRead())
            {
                eLedState = FLASH;
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
				
        case FLASH:
            if ((BUTTON_1 == eKeyboardRead())|(10 == ucBlinkOnCounter))
            {
                eLedState = STOP;
                ucBlinkOnCounter = 0;
                ucBlinkOffCounter = 0;
            }
            else
            {
                if (ucBlinkOffCounter != 0)
                {
                    ucBlinkOnCounter++;
                    ucBlinkOffCounter = 0;
                    LedOn(4);
                }
                else
                {
                    ucBlinkOffCounter = 1;
                    LedOn(3);
                }
                eLedState = FLASH;
            }
        break;
						
        default:
            break;
        }
        Delay(100);
    }
}
