#include "CAN.h"
#include "timer.h"

int main (void){
	
	unsigned char ucMsgCtr=0; 
	
	LedInit();
	Can1_InitAsTX();
	Can2_InitAsRX();
	InitTimer0();
	
	while(1){
			if (ucCan1_TxFree())  Can1_SendByte(~ucMsgCtr++);
			if (ucCan2_RxReady()) Led_ShowByte(ucCan2_ReceiveByte());
			WaitOnTimer0(100000);
	}
}
