#include <LPC21xx.H>
#include "CAN.h"

#define CAN_RD1				1<<18
#define CAN_RD2				1<<14
#define CAN_TD2				1<<16

#define RM 						1<<0
#define TBS1					1<<2
#define DLC_1_BYTE		1<<16


#define ACC_OFF 			1<<0
#define ACC_BP				1<<1
#define RRB						1<<2

#define TX_FREE				1<<2
#define RX_AV					1<<0
#define ID_11BITS			0x0000022
#define TX_REQUEST		1<<0

#define BUS_TIMING 0x001C001D

void Can1_InitAsTX(void){
	 
	PINSEL1 |= CAN_RD1;
	C1MOD = RM; 
	C1BTR = BUS_TIMING; 
	C1TFI1 = DLC_1_BYTE;
	C1MOD &= (~RM); 
}

void Can2_InitAsRX(void){
	
	PINSEL1 |= CAN_RD2 | CAN_TD2;
	C2MOD = RM; 
	C2BTR = BUS_TIMING; 
	AFMR = ACC_OFF | ACC_BP;
	C2CMR = RRB;
	C2MOD &= (~RM); 
}
 
unsigned char ucCan1_TxFree(void){
	 
	if (C1SR & TX_FREE) return 1;
	else return 0; 
}
 
 
unsigned char ucCan2_RxReady(void){
	 
	if(C2SR & RX_AV) return 1;
	else return 0;
}
 
void Can1_SendByte(unsigned char ucData){
	
	C1TID1 = ID_11BITS; 
	C1TDA1 = ucData;
	C1CMR  = TX_REQUEST;
}
 
unsigned char ucCan2_ReceiveByte(void){
	
	C2CMR = RRB;
	return C2RDA;
}
