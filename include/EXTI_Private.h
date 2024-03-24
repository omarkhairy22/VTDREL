/********************************************/
/* SWC: EXTI Driver                         */
/********************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#define EXTI_IMR			*((volatile u32*)0x40013C00)
#define EXTI_RTSR			*((volatile u32*)0x40013C08)
#define EXTI_FTSR			*((volatile u32*)0x40013C0C)
#define EXTI_SWIER			*((volatile u32*)0x40013C10)
#define EXTI_PR				*((volatile u32*)0x40013C14)

#define SYSCFG_EXTICR1		*((volatile u32*)0x40013808)
#define SYSCFG_EXTICR2		*((volatile u32*)0x4001380C)
#define SYSCFG_EXTICR3		*((volatile u32*)0x40013810)
#define SYSCFG_EXTICR4		*((volatile u32*)0x40013814)

#endif
