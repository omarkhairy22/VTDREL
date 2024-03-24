/********************************************/
/* SWC: IR Driver                           */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "IR_Interface.h"
#include "IR_Private.h"
#include "IR_Config.h"

#include "STK_Interface.h"
#include "GPIO_Interface.h"
#include "EXTI_Interface.h"

/*Global Pointer to Function*/
void (*IR_GPF)(void) = NULL;

/*****************************************************************/
/* Func. Name: IR_voidInit		                                 */
/* i/p arguments: Copy_u8PortID:								 */
/* IOA, IOB, IOC												 */
/* i/p arguments: Copy_u8LineID: 0->15		                     */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to initialize the IR Rx			 */
/*****************************************************************/
void IR_voidInit(u8 Copy_u8PortID, u8 Copy_u8LineID)
{
	GPIO_voidSetPinMode(Copy_u8PortID, Copy_u8LineID, INPUT);
	GPIO_voidSetPinPuPdConfig(Copy_u8PortID, Copy_u8LineID, INPUT_FLOATING);
	EXTI_voidSetSenseControl(FALLING_EDGE, Copy_u8LineID);
	EXTI_voidSetEXTIPinConfig(Copy_u8PortID, Copy_u8LineID);
	EXTI_voidSetCallBack(&IR_voidRecord);
	EXTI_voidSetEXTILineEnable(Copy_u8LineID);
}

/*****************************************************************/
/* Func. Name: IR_u8GetFrameAddress		                         */
/* i/p arguments: nothing                                        */
/* o/p arguments: u8                                             */
/* Desc. : This API allows user to get the address in the frame	 */
/*****************************************************************/
u8 IR_u8GetFrameAddress(void)
{
	return IR_u8Address;
}

/*****************************************************************/
/* Func. Name: IR_u8GetFrameData		                         */
/* i/p arguments: nothing                                        */
/* o/p arguments: u8                                             */
/* Desc. : This API allows user to get the data in the frame	 */
/*****************************************************************/
u8 IR_u8GetFrameData(void)
{
	return IR_u8Data;
}

/*****************************************************************/
/* Func. Name: IR_voidSetCallBack		                         */
/* i/p arguments: LPF: Pointer to function		                 */
/* o/p arguments: nothing                                        */
/* Desc. :														 */
/* This API allows user to set the call back function	 		 */
/*****************************************************************/
void IR_voidSetCallBack(void (*LPF)(void))
{
	IR_GPF = LPF;
}

void IR_voidRecord(void)
{
	static u8 Local_u8Bit = 31;
	if (!IR_u8StartFlag)
	{
		STK_voidSetIntervalSingle(15000, NULL);
		IR_u8StartFlag = 1;
	}
	else
	{
		u16 Local_u16Time = STK_u32GetElapsedTime();
		if (Local_u16Time >= 13000 && Local_u16Time <= 14000)
		{
			Local_u8Bit = 31;
		}
		else if (Local_u16Time >= 2000 && Local_u16Time <= 2500)
		{
			SET_BIT(IR_u32Temp, Local_u8Bit--);
		}
		else if (Local_u16Time >= 1000 && Local_u16Time <= 1500)
		{
			CLR_BIT(IR_u32Temp, Local_u8Bit--);
		}
		STK_voidSetIntervalSingle(15000, &IR_voidEnd);
	}
}

void IR_voidEnd(void)
{
	IR_u8StartFlag = 0;
	u8 Local_u8Address = IR_u32Temp >> 24;
	u8 Local_u8Data = 0xFF & (IR_u32Temp >> 8);
	if (Local_u8Address == (0xFF - ((IR_u32Temp >> 16) & 0xFF)) && (Local_u8Data == (0xFF - ((IR_u32Temp) & 0xFF))))
	{
		IR_u8Address = Local_u8Address;
		IR_u8Data = Local_u8Data;
		if (IR_GPF != NULL)
		{
			IR_GPF();
		}
	}
	else
	{
		// Corrupt frame
	}
}
