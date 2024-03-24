/********************************************/
/* SWC: IR Driver                           */
/********************************************/
#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H

void IR_voidInit(u8 Copy_u8PortID, u8 Copy_u8LineID);
u8 IR_u8GetFrameAddress(void);
u8 IR_u8GetFrameData(void);
void IR_voidSetCallBack(void (*LPF)(void));

#endif
