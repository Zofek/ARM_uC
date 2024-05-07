#include "i2c.h"
#include <LPC21xx.H>

#define SCL_bm 01<<4
#define SDA_bm 01<<6

#define	STO		1<<4
#define STA		1<<5
#define I2EN	1<<6

#define AAC		1<<2
#define SIC		1<<3
#define STAC	1<<5
#define I2ENC	1<<6

#define VIC_I2C_CHANNEL_NR 9
#define mIRQ_SLOT_ENABLE 1<<5

#define SLAVE_ADDRESS 0x20

#define START_CONDITION 0x08
#define ADDRESS_TRANSMITTED 0x18
#define ADDRESS_SEND_NO_ACK 0x20
#define DATA_TRANSMITTED 0x28
#define DATA_SEND_NO_ACK 0x30

unsigned char ucI2CBuffer = 0;
unsigned int uiErrorCode = 0;

__irq void I2C_Interrupt(void){
	
	switch(I2STAT)
	{
		case START_CONDITION:
			I2DAT= (SLAVE_ADDRESS<<1);
			I2CONCLR= STAC;
			break;
		case ADDRESS_TRANSMITTED:
			I2DAT= ucI2CBuffer;
			break;
		case ADDRESS_SEND_NO_ACK:
			I2CONSET= STO | STA;
			break;
		case DATA_TRANSMITTED:
			I2CONSET= STO;
			break;
		case DATA_SEND_NO_ACK:
			I2CONSET= STO | STA;
			break;
		default :
			break;
	}
	//uiErrorCode = (I2STAT << 16);
	//IO1SET = uiErrorCode;
	I2CONCLR= SIC;
	VICVectAddr=0x00;
}
	
void I2C_Init(void){
	
	PINSEL0 = PINSEL0 | SCL_bm | SDA_bm;
	
	I2CONCLR= AAC | SIC | STAC | I2ENC;
	I2CONSET=I2EN;
	I2SCLH=0x80;
	I2SCLL=0x80;
	
	VICIntSelect = 0x0;
	VICIntEnable |= (0x1 << VIC_I2C_CHANNEL_NR);
	VICVectCntl1 = mIRQ_SLOT_ENABLE | VIC_I2C_CHANNEL_NR; 
	VICVectAddr1 = (unsigned long)I2C_Interrupt;
}

void PCF8574_Write(unsigned char ucData){
	
	I2CONSET = STA;
	ucI2CBuffer = ucData;
}
