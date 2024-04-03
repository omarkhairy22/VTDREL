/********************************************/
/* SWC: TIM4 Driver                         */
/********************************************/
#ifndef TIM4_INTERFACE_H
#define TIM4_INTERFACE_H

void TIM4_voidInit(void);
void TIM4_voidSetBusyWait(u16 Copy_u16Ticks);
void TIM4_voidSetIntervalSingle(u16 Copy_u16Ticks, void (*LpF)(void));
void TIM4_voidSetIntervalPeriodic(u16 Copy_u16Ticks, void (*LpF)(void));
u16 TIM4_u16GetElapsedTime(void);
u16 TIM4_u16GetRemainingTime(void);

#endif
