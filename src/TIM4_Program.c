/********************************************/
/* SWC: TIM4 Driver                         */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM4_Interface.h"
#include "TIM4_Private.h"
#include "TIM4_Config.h"

/*Global Pointer to Function*/
void (*TIM4_GpF)(void) = NULL;

void TIM4_voidInit(void)
{
	/*1- Disable Timer*/
	CLR_BIT(TIM4_CR1, 0);
	/*2- Select update request source*/
	SET_BIT(TIM4_CR1, 2);
	/*3- Set as an down counter*/
	SET_BIT(TIM4_CR1, 4);
	/*4- Disable INT*/
	CLR_BIT(TIM4_DIER, 0);
	/*5- Select Timer Clock Source*/
	#if TIM4_CLK_PSC != 0
		TIM4_PSC = TIM4_CLK_PSC - 1;
	#else
		#warning "Invalid Option"
	#endif
}

void TIM4_voidSetBusyWait(u16 Copy_u16Ticks)
{
	/*1- Reload The value in the ARR*/
	TIM4_ARR = Copy_u16Ticks;
	/*2- Start Timer*/
	SET_BIT(TIM4_CR1, 0);
	/*3- Update CNT*/
	SET_BIT(TIM4_EGR, 0);
	CLR_BIT(TIM4_SR, 0);
	/*4- Wait until the flag is raised*/
	while(!GET_BIT(TIM4_SR, 0));
	/*5- Stop the timer*/
	CLR_BIT(TIM4_CR1, 0);
	CLR_BIT(TIM4_SR, 0);
	TIM4_ARR = 0;
	TIM4_CNT = 0;
}

void TIM4_voidSetIntervalSingle(u16 Copy_u16Ticks, void (*LpF)(void))
{
	/*1- Reload The value in the ARR*/
    TIM4_ARR = Copy_u16Ticks;
    if (GET_BIT(TIM4_CR1, 0))
    {
    	SET_BIT(TIM4_CR1, 1);
    	SET_BIT(TIM4_EGR, 0);
    	CLR_BIT(TIM4_CR1, 1);
    }
    /*2- Start Timer*/
    SET_BIT(TIM4_CR1, 0);
    /*3- Clear Interrupt flag*/
    CLR_BIT(TIM4_SR, 0);
    /*4- Enable one-time mode */
    SET_BIT(TIM4_CR1, 3);
    /*5- Save CallBack*/
    TIM4_GpF = LpF;
    /*6- Enable INT*/
    SET_BIT(TIM4_DIER, 0);
}

void TIM4_voidSetIntervalPeriodic(u16 Copy_u16Ticks, void (*LpF)(void))
{
	/*1- Reload The value in the ARR*/
    TIM4_ARR = Copy_u16Ticks;
    if (GET_BIT(TIM4_CR1, 0))
    {
    	SET_BIT(TIM4_CR1, 1);
    	SET_BIT(TIM4_EGR, 0);
    	CLR_BIT(TIM4_CR1, 1);
    }
    /*2- Start Timer*/
    SET_BIT(TIM4_CR1, 0);
    /*3- Clear Interrupt flag*/
    CLR_BIT(TIM4_SR, 0);
    /*4- Disable one-time mode */
    CLR_BIT(TIM4_CR1, 3);
    /*5- Save CallBack*/
    TIM4_GpF = LpF;
    /*6- Enable INT*/
    SET_BIT(TIM4_DIER, 0);
}

u16 TIM4_u16GetElapsedTime(void)
{
	return (TIM4_ARR - TIM4_CNT);
}

u16 TIM4_u16GetRemainingTime(void)
{
	return TIM4_CNT;
}

void TIM4_IRQHandler()
{
	if (!GET_BIT(TIM4_CR1, 0))
	{
		CLR_BIT(TIM4_DIER, 0);
		CLR_BIT(TIM4_CR1, 3);
		TIM4_ARR = 0;
	}
	if (TIM4_GpF != NULL)
	{
		TIM4_GpF();
	}
	CLR_BIT(TIM4_SR, 0);
}
