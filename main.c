#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiMiliseconds){
	
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (uiMiliseconds * 5452); uiCounter++){}
}

int main()
{
		LedInit();
		KeyboardInit();
		
		while(1)
		{
				switch (eKeyboardRead())
				{
					case BUTTON_1:
					LedStepRight();	
					break;
					
					case BUTTON_2:
					LedStepLeft();	
					break;
					
					default:
					break;
				}
				Delay(250);
		}
}
