#ifndef CAN_H_
#define CAN_H_

#include "led.h"

void CanInit(void);
void Can1_InitAsTX( void );
void Can2_InitAsRX(void);
unsigned char ucCan1_TxFree(void);
unsigned char ucCan2_RxReady(void);
void Can1_SendByte(unsigned char ucData);
unsigned char ucCan2_ReceiveByte(void);

#endif
