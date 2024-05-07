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
	S0SPCCR = CLK_COUNTER_bm;
}
//-----------------------------------------------------------------------
void DAC_MCP4921_Set(unsigned int uiVoltage) {
	
	unsigned int uiData = 0;

	IO0CLR |= CS_bm;

	uiData = 0x3000 | uiVoltage;
	uiData >>= 8;
	S0SPDR = uiData;
	while(!(S0SPSR & SPIF_bm)) {} 
	
	uiData = 0x00FF & uiVoltage;	
	S0SPDR = uiData;
	while(!(S0SPSR & SPIF_bm)) {} 

	IO0SET |= CS_bm;
}

//-----------------------------------------------------------------------
void DAC_MCP4921_Set_mV(unsigned int uiVoltage) {
	
	unsigned int uiData = 0; 
	
	if (uiVoltage <= 3300) {
		uiData = (4096*uiVoltage)/3300;
	}
	else  {
		uiData = (4096*3299)/3300;
	}
	DAC_MCP4921_Set(uiData);
	
}

int main () {
	
	unsigned int uiStep,uiSiny_Val = 0;
	
	DAC_MCP4921_Initialize();

	while(1) { 
		
		uiSiny_Val = (unsigned int)(1000*(1 + sin((double)(uiStep * (PI/180)))));
		uiStep = (uiStep + 1) % 360;
		
		DAC_MCP4921_Set_mV(uiSiny_Val);

	}
}
