/********************************************/
/* SWC: TIM2 Driver                         */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIM2_Interface.h"
#include "TIM2_Private.h"
#include "TIM2_Config.h"

/*Global Pointer to Function*/
void (*TIM2_GpF)(void) = NULL;

void TIM2_voidInit(void)
{
	/*1- Disable Timer*/
	CLR_BIT(TIM2_CR1, 0);
	/*2- Select update request source*/
	SET_BIT(TIM2_CR1, 2);
	/*3- Set as an down counter*/
	SET_BIT(TIM2_CR1, 4);
	/*4- Disable INT*/
	CLR_BIT(TIM2_DIER, 0);
	/*5- Select Timer Clock Source*/
	#if TIM2_CLK_PSC != 0
		TIM2_PSC = TIM2_CLK_PSC - 1;
	#else
		#warning "Invalid Option"
	#endif
}

void TIM2_voidSetBusyWait(u32 Copy_u32Ticks)
{
	/*1- Reload The value in the ARR*/
	TIM2_ARR = Copy_u32Ticks;
	/*2- Start Timer*/
	SET_BIT(TIM2_CR1, 0);
	/*3- Update CNT*/
	SET_BIT(TIM2_EGR, 0);
	CLR_BIT(TIM2_SR, 0);
	/*4- Wait until the flag is raised*/
	while(!GET_BIT(TIM2_SR, 0));
	/*5- Stop the timer*/
	CLR_BIT(TIM2_CR1, 0);
	CLR_BIT(TIM2_SR, 0);
	TIM2_ARR = 0;
	TIM2_CNT = 0;
}

void TIM2_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*LpF)(void))
{
	/*1- Reload The value in the ARR*/
    TIM2_ARR = Copy_u32Ticks;
    if (GET_BIT(TIM2_CR1, 0))
    {
    	SET_BIT(TIM2_CR1, 1);
    	SET_BIT(TIM2_EGR, 0);
    	CLR_BIT(TIM2_CR1, 1);
    }
    /*2- Start Timer*/
    SET_BIT(TIM2_CR1, 0);
    /*3- Clear Interrupt flag*/
    CLR_BIT(TIM2_SR, 0);
    /*4- Enable one-time mode */
    SET_BIT(TIM2_CR1, 3);
    /*5- Save CallBack*/
    TIM2_GpF = LpF;
    /*6- Enable INT*/
    SET_BIT(TIM2_DIER, 0);
}

void TIM2_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*LpF)(void))
{
	/*1- Reload The value in the ARR*/
    TIM2_ARR = Copy_u32Ticks;
    if (GET_BIT(TIM2_CR1, 0))
    {
    	SET_BIT(TIM2_CR1, 1);
    	SET_BIT(TIM2_EGR, 0);
    	CLR_BIT(TIM2_CR1, 1);
    }
    /*2- Start Timer*/
    SET_BIT(TIM2_CR1, 0);
    /*3- Clear Interrupt flag*/
    CLR_BIT(TIM2_SR, 0);
    /*4- Disable one-time mode */
    CLR_BIT(TIM2_CR1, 3);
    /*5- Save CallBack*/
    TIM2_GpF = LpF;
    /*6- Enable INT*/
    SET_BIT(TIM2_DIER, 0);
}

u32 TIM2_u32GetElapsedTime(void)
{
	return (TIM2_ARR - TIM2_CNT);
}

u32 TIM2_u32GetRemainingTime(void)
{
	return TIM2_CNT;
}

void TIM2_IRQHandler()
{
	if (!GET_BIT(TIM2_CR1, 0))
	{
		CLR_BIT(TIM2_DIER, 0);
		CLR_BIT(TIM2_CR1, 3);
		TIM2_ARR = 0;
	}
	if (TIM2_GpF != NULL)
	{
		TIM2_GpF();
	}
	CLR_BIT(TIM2_SR, 0);
}
