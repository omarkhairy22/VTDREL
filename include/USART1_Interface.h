/********************************************/
/* SWC: USART1 Driver                       */
/********************************************/
#ifndef USART1_INTERFACE_H
#define USART1_INTERFACE_H

void USART1_voidInit(void);
void USART1_voidTransmit(u8 Copy_u8Data);
u8 USART1_u8Receive(void);
u8 USART1_u8Trancieve(u8 Copy_u8Data);
void USART1_voidEnableRxINT(void);
void USART1_voidDisableRxINT(void);
void USART1_voidSetCallBack(void (*LpF)(void));
void USART1_voidEnableRxDMA(void);
void USART1_voidDisableRxDMA(void);

#endif
