#include <LPC21xx.H>
#include "math.h"

//-----------------------------------------------------------------------
#define SCK_bm (1<<8)
#define MISO_bm (1<<10)
#define MOSI_bm (1<<12)
#define SSEL_bm (1<<14)
#define CS_bm (1<<10)
#define MSTR_bm (1<<5)
#define CPHA_bm (1<<3)
#define CPOL_bm (1<<4)
#define CLK_COUNTER_bm (1<<3)
#define SPIF_bm (1<<7)

#define PI 3.14159265

//-----------------------------------------------------------------------
void DAC_MCP4921_Initialize(void) {
	
	PINSEL0 |= (SCK_bm | MISO_bm | MOSI_bm | SSEL_bm); 
	IO0DIR |= CS_bm;
	IO0SET |= CS_bm;
	S0SPCR |= MSTR_bm;
	S0SPCR &= ~(CPHA_bm | CPOL_bm);
	S0SPCCR = 0xFF;
}

//-----------------------------------------------------------------------
void DAC_MCP4921_Set(unsigned int uiVoltage) {
		
	IO0CLR |= CS_bm;
	
	S0SPDR = uiVoltage>>8;
	while(!(S0SPSR & SPIF_bm)) {}
		
	S0SPDR = uiVoltage & 0x00FF;	
	while(!(S0SPSR & SPIF_bm)) {}
		
	IO0SET |= CS_bm;
}

//-----------------------------------------------------------------------
void DAC_MCP4921_Set_mV(unsigned int uiVoltage) {
	
	unsigned int uiData; 
	
	if (uiVoltage <= 3300) {
		uiData = (4096*uiVoltage)/3300;
	}
	else  {
		uiData = (4096*3299)/3300;
	}
	DAC_MCP4921_Set(uiData);
	
}

//-----------------------------------------------------------------------
void Delay(unsigned int uiMiliseconds){
	
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter <= (uiMiliseconds * 5452); uiCounter++){}
}
//-----------------------------------------------------------------------
int main () {

	unsigned char ucIndex = 0;		
	
	DAC_MCP4921_Initialize();
	
	while(1) {
		
		Delay(10);
		
		DAC_MCP4921_Set(0xAF00 | ucIndex);
		ucIndex++;
	}
}
