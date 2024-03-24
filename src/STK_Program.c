/********************************************/
/* SWC: STK Driver                          */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_Private.h"
#include "STK_Interface.h"
#include "STK_Config.h"

/*Global Pointer to Function*/
void (*GpF)(void) = NULL;
/*Global Variable for Interval Mode*/
u8 Global_u8ModeOfInterval = 0;

void STK_voidInit()
{
    /*1- Disable SysTick*/
    CLR_BIT(STK_CTRL, 0);
    /*2- Disable SysTick INT*/
    CLR_BIT(STK_CTRL, 1);
    /*3- Select SysTick Clock Source*/
    #if STK_CLK_SRC == AHB_DIV_BY_8
        CLR_BIT(STK_CTRL, 2);
    #elif STK_CLK_SRC == AHB
        SET_BIT(STK_CTRL, 2);
    #else
        #warning "Invalid Option"
    #endif
}

/*Tick Time = 1 microsecond that means 1000 = 1 milli second*/
void STK_voidSetBusyWait(u32 Copy_u32Ticks)
{
    /*1- Reload The value in the LOAD*/
    STK_LOAD = Copy_u32Ticks;

    /*2- Start Timer*/
    SET_BIT(STK_CTRL, 0);

    /*3- Wait until the flag is raised*/
    while(GET_BIT(STK_CTRL,16) == 0);   //while(!GET_BIT(STK_CTRL,16));

    /*4- Stop Timer*/
    CLR_BIT(STK_CTRL, 0);
    STK_LOAD = 0;
    STK_VAL = 0;
}

void STK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*LpF)(void))
{
	/*1- Clear The value in the VAL*/
	STK_VAL = 0;

    /*2- Reload The value in the LOAD*/
    STK_LOAD = Copy_u32Ticks;

    /*3- Start Timer*/
    SET_BIT(STK_CTRL, 0);

    /*4- Save CallBack*/
    GpF = LpF;

    /*5 - Set Mode of Interval*/
    Global_u8ModeOfInterval = SINGLE_INTERVAL_MODE;

    /*6- Enable SysTick INT*/
    SET_BIT(STK_CTRL, 1);
}

void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*LpF)(void))
{
	/*1- Clear The value in the VAL*/
	STK_VAL = 0;

    /*2- Reload The value in the LOAD*/
    STK_LOAD = Copy_u32Ticks;

    /*3- Start Timer*/
    SET_BIT(STK_CTRL, 0);

    /*4- Save CallBack*/
    GpF = LpF;

    /*5 - Set Mode of Interval*/
    Global_u8ModeOfInterval = PERIODIC_INTERVAL_MODE;

    /*6- Enable SysTick INT*/
    SET_BIT(STK_CTRL, 1);
}

u32  STK_u32GetElapsedTime(void)
{
    return (STK_LOAD - STK_VAL);
}

u32  STK_u32GetRemainingTime(void)
{
    return STK_VAL;
}


void SysTick_Handler()
{
    if(Global_u8ModeOfInterval == SINGLE_INTERVAL_MODE)
    {
        /*Disable Int*/
        CLR_BIT(STK_CTRL, 1);
        /*Stop Timer*/
        CLR_BIT(STK_CTRL, 0);
        STK_LOAD = 0;
        STK_VAL = 0;
    }
    if(GpF != NULL)
    {
        GpF();
    }
    /*Clear Flag*/
    if (GET_BIT(STK_CTRL, 16))
    {
        /*Do Nothing*/
    }
}
