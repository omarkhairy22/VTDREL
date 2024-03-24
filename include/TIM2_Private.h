/********************************************/
/* SWC: TIM2 Driver                         */
/********************************************/
#ifndef TIM2_PRIVATE_H
#define TIM2_PRIVATE_H

#define TIM2_CR1		*((volatile u32*)0x40000000)
#define TIM2_DIER		*((volatile u32*)0x4000000C)
#define TIM2_SR			*((volatile u32*)0x40000010)
#define TIM2_EGR		*((volatile u16*)0x40000014)
#define TIM2_CNT		*((volatile u32*)0x40000024)
#define TIM2_PSC		*((volatile u16*)0x40000028)
#define TIM2_ARR		*((volatile u32*)0x4000002C)

#endif
