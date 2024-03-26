/********************************************/
/* SWC: TIM3 Driver                         */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM3_Interface.h"
#include "TIM3_Private.h"
#include "TIM3_Config.h"

/*Global Pointer to Function*/
void (*TIM3_GpF)(void) = NULL;

void TIM3_voidInit(void)
{
	/*1- Disable Timer*/
	CLR_BIT(TIM3_CR1, 0);
	/*2- Select update request source*/
	SET_BIT(TIM3_CR1, 2);
	/*3- Set as an down counter*/
	SET_BIT(TIM3_CR1, 4);
	/*4- Disable INT*/
	CLR_BIT(TIM3_DIER, 0);
	/*5- Select Timer Clock Source*/
	#if TIM3_CLK_PSC != 0
		TIM3_PSC = TIM3_CLK_PSC - 1;
	#else
		#warning "Invalid Option"
	#endif
}

void TIM3_voidSetBusyWait(u16 Copy_u16Ticks)
{
	/*1- Reload The value in the ARR*/
	TIM3_ARR = Copy_u16Ticks;
	/*2- Start Timer*/
	SET_BIT(TIM3_CR1, 0);
	/*3- Update CNT*/
	SET_BIT(TIM3_EGR, 0);
	CLR_BIT(TIM3_SR, 0);
	/*4- Wait until the flag is raised*/
	while(!GET_BIT(TIM3_SR, 0));
	/*5- Stop the timer*/
	CLR_BIT(TIM3_CR1, 0);
	CLR_BIT(TIM3_SR, 0);
	TIM3_ARR = 0;
	TIM3_CNT = 0;
}

void TIM3_voidSetIntervalSingle(u16 Copy_u16Ticks, void (*LpF)(void))
{
	/*1- Reload The value in the ARR*/
    TIM3_ARR = Copy_u16Ticks;
    if (GET_BIT(TIM3_CR1, 0))
    {
    	SET_BIT(TIM3_CR1, 1);
    	SET_BIT(TIM3_EGR, 0);
    	CLR_BIT(TIM3_CR1, 1);
    }
    /*2- Start Timer*/
    SET_BIT(TIM3_CR1, 0);
    /*3- Clear Interrupt flag*/
    CLR_BIT(TIM3_SR, 0);
    /*4- Enable one-time mode */
    SET_BIT(TIM3_CR1, 3);
    /*5- Save CallBack*/
    TIM3_GpF = LpF;
    /*6- Enable INT*/
    SET_BIT(TIM3_DIER, 0);
}

void TIM3_voidSetIntervalPeriodic(u16 Copy_u16Ticks, void (*LpF)(void))
{
	/*1- Reload The value in the ARR*/
    TIM3_ARR = Copy_u16Ticks;
    if (GET_BIT(TIM3_CR1, 0))
    {
    	SET_BIT(TIM3_CR1, 1);
    	SET_BIT(TIM3_EGR, 0);
    	CLR_BIT(TIM3_CR1, 1);
    }
    /*2- Start Timer*/
    SET_BIT(TIM3_CR1, 0);
    /*3- Clear Interrupt flag*/
    CLR_BIT(TIM3_SR, 0);
    /*4- Disable one-time mode */
    CLR_BIT(TIM3_CR1, 3);
    /*5- Save CallBack*/
    TIM3_GpF = LpF;
    /*6- Enable INT*/
    SET_BIT(TIM3_DIER, 0);
}

u16 TIM3_u16GetElapsedTime(void)
{
	return (TIM3_ARR - TIM3_CNT);
}

u16 TIM3_u16GetRemainingTime(void)
{
	return TIM3_CNT;
}

void TIM3_IRQHandler()
{
	if (!GET_BIT(TIM3_CR1, 0))
	{
		CLR_BIT(TIM3_DIER, 0);
		CLR_BIT(TIM3_CR1, 3);
		TIM3_ARR = 0;
	}
	if (TIM3_GpF != NULL)
	{
		TIM3_GpF();
	}
	CLR_BIT(TIM3_SR, 0);
}
