/********************************************/
/* SWC: TIM4 Driver                         */
/********************************************/
#ifndef TIM4_PRIVATE_H
#define TIM4_PRIVATE_H

#define TIM4_CR1		*((volatile u32*)0x40000800)
#define TIM4_DIER		*((volatile u32*)0x4000080C)
#define TIM4_SR			*((volatile u32*)0x40000810)
#define TIM4_EGR		*((volatile u16*)0x40000814)
#define TIM4_CNT		*((volatile u16*)0x40000824)
#define TIM4_PSC		*((volatile u16*)0x40000828)
#define TIM4_ARR		*((volatile u16*)0x4000082C)

#endif
