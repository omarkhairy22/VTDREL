/********************************************/
/* SWC: EXTI Driver                         */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

/*Global Pointer to Function*/
void (*EXTI_GPF)(void) = NULL;

/*****************************************************************/
/* Func. Name: EXTI_voidSetEXTILineEnable                        */
/* i/p arguments: Copy_u8LineID: 0->22		                     */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to enable an EXTI line			 */
/*****************************************************************/
void EXTI_voidSetEXTILineEnable(u8 Copy_u8LineID)
{
	if (Copy_u8LineID < 19 || Copy_u8LineID == 21 || Copy_u8LineID == 22)
	{
		SET_BIT(EXTI_IMR, Copy_u8LineID);
	}
}

/*****************************************************************/
/* Func. Name: EXTI_voidSetEXTILineDisable                       */
/* i/p arguments: Copy_u8LineID: 0->22		                     */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to disable an EXTI line			 */
/*****************************************************************/
void EXTI_voidSetEXTILineDisable(u8 Copy_u8LineID)
{
	if (Copy_u8LineID < 19 || Copy_u8LineID == 21 || Copy_u8LineID == 22)
	{
		CLR_BIT(EXTI_IMR, Copy_u8LineID);
	}
}

/*****************************************************************/
/* Func. Name: EXTI_voidSetSenseControl                          */
/* i/p arguments: Copy_u8SenseControl:							 */
/* RISING_EDGE, FALLING_EDGE, ON_CHANGE							 */
/* i/p arguments: Copy_u8LineID: 0->22		                     */
/* o/p arguments: nothing                                        */
/* Desc. :														 */
/* This API allows user to set the trigger of an EXTI line		 */
/*****************************************************************/
void EXTI_voidSetSenseControl(u8 Copy_u8SenseControl, u8 Copy_u8LineID)
{
	switch(Copy_u8SenseControl)
	{
	case RISING_EDGE:
		SET_BIT(EXTI_RTSR, Copy_u8LineID);
		CLR_BIT(EXTI_FTSR, Copy_u8LineID);
		break;
	case FALLING_EDGE:
		CLR_BIT(EXTI_RTSR, Copy_u8LineID);
		SET_BIT(EXTI_FTSR, Copy_u8LineID);
		break;
	case ON_CHANGE:
		SET_BIT(EXTI_RTSR, Copy_u8LineID);
		SET_BIT(EXTI_FTSR, Copy_u8LineID);
	}
}


/*****************************************************************/
/* Func. Name: EXTI_voidSetEXTIPinConfig                         */
/* i/p arguments: Copy_u8PortID:								 */
/* EXTI_PORTA, EXTI_PORTB, EXTI_PORTC							 */
/* i/p arguments: Copy_u8LineID: 0->22		                     */
/* o/p arguments: nothing                                        */
/* Desc. :														 */
/* This API allows user to set the port of an EXTI line 		 */
/*****************************************************************/
void EXTI_voidSetEXTIPinConfig(u8 Copy_u8PortID, u8 Copy_u8LineID)
{
	switch(Copy_u8PortID)
	{
	case EXTI_PORTA:
		if (Copy_u8LineID < 4)
		{
			CLR_BIT(SYSCFG_EXTICR1, (0 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (1 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (2 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (3 + Copy_u8LineID * 4));
		}
		else if (Copy_u8LineID < 8)
		{
			CLR_BIT(SYSCFG_EXTICR2, (0 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (1 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (2 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (3 + (Copy_u8LineID - 4) * 4));
		}
		else if (Copy_u8LineID < 12)
		{
			CLR_BIT(SYSCFG_EXTICR3, (0 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (1 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (2 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (3 + (Copy_u8LineID - 8) * 4));
		}
		else
		{
			CLR_BIT(SYSCFG_EXTICR4, (0 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (1 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (2 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (3 + (Copy_u8LineID - 12) * 4));
		}
		break;
	case EXTI_PORTB:
		if (Copy_u8LineID < 4)
		{
			SET_BIT(SYSCFG_EXTICR1, (0 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (1 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (2 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (3 + Copy_u8LineID * 4));
		}
		else if (Copy_u8LineID < 8)
		{
			SET_BIT(SYSCFG_EXTICR2, (0 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (1 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (2 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (3 + (Copy_u8LineID - 4) * 4));
		}
		else if (Copy_u8LineID < 12)
		{
			SET_BIT(SYSCFG_EXTICR3, (0 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (1 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (2 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (3 + (Copy_u8LineID - 8) * 4));
		}
		else
		{
			SET_BIT(SYSCFG_EXTICR4, (0 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (1 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (2 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (3 + (Copy_u8LineID - 12) * 4));
		}
		break;
	case EXTI_PORTC:
		if (Copy_u8LineID < 4)
		{
			CLR_BIT(SYSCFG_EXTICR1, (0 + Copy_u8LineID * 4));
			SET_BIT(SYSCFG_EXTICR1, (1 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (2 + Copy_u8LineID * 4));
			CLR_BIT(SYSCFG_EXTICR1, (3 + Copy_u8LineID * 4));
		}
		else if (Copy_u8LineID < 8)
		{
			CLR_BIT(SYSCFG_EXTICR2, (0 + (Copy_u8LineID - 4) * 4));
			SET_BIT(SYSCFG_EXTICR2, (1 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (2 + (Copy_u8LineID - 4) * 4));
			CLR_BIT(SYSCFG_EXTICR2, (3 + (Copy_u8LineID - 4) * 4));
		}
		else if (Copy_u8LineID < 12)
		{
			CLR_BIT(SYSCFG_EXTICR3, (0 + (Copy_u8LineID - 8) * 4));
			SET_BIT(SYSCFG_EXTICR3, (1 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (2 + (Copy_u8LineID - 8) * 4));
			CLR_BIT(SYSCFG_EXTICR3, (3 + (Copy_u8LineID - 8) * 4));
		}
		else
		{
			CLR_BIT(SYSCFG_EXTICR4, (0 + (Copy_u8LineID - 12) * 4));
			SET_BIT(SYSCFG_EXTICR4, (1 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (2 + (Copy_u8LineID - 12) * 4));
			CLR_BIT(SYSCFG_EXTICR4, (3 + (Copy_u8LineID - 12) * 4));
		}
	}
}

/*****************************************************************/
/* Func. Name: EXTI_voidSetEXTISWI		                         */
/* i/p arguments: Copy_u8LineID: 0->22		                     */
/* o/p arguments: nothing                                        */
/* Desc. :														 */
/* This API allows user to enable an EXTI software interrupt  	 */
/*****************************************************************/
void EXTI_voidSetEXTISWI(u8 Copy_u8LineID)
{
	if (Copy_u8LineID < 19 || Copy_u8LineID == 21 || Copy_u8LineID == 22)
	{
		SET_BIT(EXTI_SWIER, Copy_u8LineID);
	}
}

/*****************************************************************/
/* Func. Name: EXTI_voidSetCallBack		                         */
/* i/p arguments: LPF: Pointer to function		                 */
/* o/p arguments: nothing                                        */
/* Desc. :														 */
/* This API allows user to set the call back function	 		 */
/*****************************************************************/
void EXTI_voidSetCallBack(void (*LPF)(void))
{
	EXTI_GPF = LPF;
}

void EXTI0_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    SET_BIT(EXTI_PR, 0);
}

void EXTI1_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    SET_BIT(EXTI_PR, 1);
}

void EXTI2_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    SET_BIT(EXTI_PR, 2);
}

void EXTI3_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    SET_BIT(EXTI_PR, 3);
}

void EXTI4_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    SET_BIT(EXTI_PR, 4);
}

void EXTI9_5_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    if (GET_BIT(EXTI_PR, 5))
    {
    	SET_BIT(EXTI_PR, 5);
    }
    else if (GET_BIT(EXTI_PR, 6))
    {
    	SET_BIT(EXTI_PR, 6);
    }
    else if (GET_BIT(EXTI_PR, 7))
    {
    	SET_BIT(EXTI_PR, 7);
    }
    else if (GET_BIT(EXTI_PR, 8))
    {
    	SET_BIT(EXTI_PR, 8);
    }
    else
    {
    	SET_BIT(EXTI_PR, 9);
    }
}

void EXTI15_10_IRQHandler()
{
    if(EXTI_GPF != NULL)
    {
        EXTI_GPF();
    }
    if (GET_BIT(EXTI_PR, 10))
    {
    	SET_BIT(EXTI_PR, 10);
    }
    else if (GET_BIT(EXTI_PR, 11))
    {
    	SET_BIT(EXTI_PR, 11);
    }
    else if (GET_BIT(EXTI_PR, 12))
    {
    	SET_BIT(EXTI_PR, 12);
    }
    else if (GET_BIT(EXTI_PR, 13))
    {
    	SET_BIT(EXTI_PR, 13);
    }
    else if (GET_BIT(EXTI_PR, 14))
    {
    	SET_BIT(EXTI_PR, 14);
    }
    else
    {
    	SET_BIT(EXTI_PR, 15);
    }
}
