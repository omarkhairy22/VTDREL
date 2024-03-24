/********************************************/
/* SWC: TIM2 Driver                         */
/********************************************/
#ifndef TIM2_INTERFACE_H
#define TIM2_INTERFACE_H

void TIM2_voidInit(void);
void TIM2_voidSetBusyWait(u32 Copy_u32Ticks);
void TIM2_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*LpF)(void));
void TIM2_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*LpF)(void));
u32 TIM2_u32GetElapsedTime(void);
u32 TIM2_u32GetRemainingTime(void);

#endif
