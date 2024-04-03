/********************************************/
/* SWC: USART1 Driver                       */
/********************************************/
#ifndef USART1_PRIVATE_H
#define USART1_PRIVATE_H

#define USART1_SR				*((volatile u16*)0x40011000)
#define USART1_DR				*((volatile u16*)0x40011004)
#define USART1_BRR				*((volatile u16*)0x40011008)
#define USART1_CR1				*((volatile u16*)0x4001100C)
#define USART1_CR2				*((volatile u16*)0x40011010)
#define USART1_CR3				*((volatile u16*)0x40011014)

#endif
