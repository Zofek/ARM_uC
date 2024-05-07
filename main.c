#include "timer.h"
#include "keyboard.h"
#include "led.h"

int main(){
		
	LedInit();
	InitTimer0Match0(250000);
	
			while(1)
	{
			LedStepLeft();
			WaitOnTimer0Match0();
	}
}
