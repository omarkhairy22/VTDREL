/********************************************/
/* SWC: TIM3 Driver                         */
/********************************************/
#ifndef TIM3_PRIVATE_H
#define TIM3_PRIVATE_H

#define TIM3_CR1		*((volatile u32*)0x40000400)
#define TIM3_DIER		*((volatile u32*)0x4000040C)
#define TIM3_SR			*((volatile u32*)0x40000410)
#define TIM3_EGR		*((volatile u16*)0x40000414)
#define TIM3_CNT		*((volatile u16*)0x40000424)
#define TIM3_PSC		*((volatile u16*)0x40000428)
#define TIM3_ARR		*((volatile u16*)0x4000042C)

#endif
