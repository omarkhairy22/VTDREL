/********************************************/
/* SWC: TIM3 Driver                         */
/********************************************/
#ifndef TIM3_INTERFACE_H
#define TIM3_INTERFACE_H

void TIM3_voidInit(void);
void TIM3_voidSetBusyWait(u16 Copy_u16Ticks);
void TIM3_voidSetIntervalSingle(u16 Copy_u16Ticks, void (*LpF)(void));
void TIM3_voidSetIntervalPeriodic(u16 Copy_u16Ticks, void (*LpF)(void));
u16 TIM3_u16GetElapsedTime(void);
u16 TIM3_u16GetRemainingTime(void);

#endif
