/********************************************/
/* SWC: DMA2 Driver                         */
/********************************************/
/*File Guard*/
#ifndef DMA2_INTERFACE_H
#define DMA2_INTERFACE_H

void DMA2_voidChannelInit(u8 Copy_u8Stream, u8 Copy_u8Channel, u8 Copy_u8Direction);
void DMA2_voidStart(u8 Copy_u8Stream, u32 Copy_u32Source, u32 Copy_u32Destination, u16 Copy_u16NumberOfItems);
void DMA2_voidSetCallBack(void (*LPF)(void));

#define S0				0
#define S1				1
#define S2				2
#define S3				3
#define S4				4
#define S5				5
#define S6				6
#define S7				7

#define CH0				0
#define CH1				1
#define CH2				2
#define CH3				3
#define CH4				4
#define CH5				5
#define CH6				6
#define CH7				7

#define PTM				0
#define MTP				1
#define MTM				2

#define USART1_ADDR		0x40011004


#endif
