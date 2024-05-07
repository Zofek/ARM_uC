#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0) //0x00000001
#define COUNTER_RESET (1<<1) //0x00000002
#define MR0_RESET (1<<1) 
#define MR0_INTERRUPT (1<<0) 
#define MR0_INTERRUPT_FLAGUE (1<<0) 

void InitTimer0(void){
	T0TCR = COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiMicroSeconds){
	T0TCR = (T0TCR | COUNTER_RESET);
	T0TCR = (T0TCR & ~(COUNTER_RESET));
	while(T0TC<(15 * uiMicroSeconds)){}
}

void InitTimer0Match0(unsigned int iDelayTime){	
	T0MR0 = (15*iDelayTime);
	T0MCR = T0MCR|(MR0_RESET | MR0_INTERRUPT);
  T0TCR = (T0TCR|COUNTER_RESET);
	T0TCR = COUNTER_ENABLE; 
}

void WaitOnTimer0Match0(void){
		while(T0IR != MR0_INTERRUPT_FLAGUE){}
		T0IR = MR0_INTERRUPT_FLAGUE;
}
