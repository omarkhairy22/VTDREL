/********************************************/
/* SWC: GSM Driver                          */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GSM_Interface.h"
#include "GSM_Config.h"
#include "GSM_Private.h"

#include "USART1_Interface.h"
#include "DMA2_Interface.h"
#include "TIM4_Interface.h"

/*Global Pointer to Function*/
void (*GSM_GpF)(void) = NULL;

volatile u8 GSM_u8MessageBuffer[PN_STRLENGTH + 5];

void GSM_voidInit(void)
{
	GSM_voidSendCMD((u8*)"AT", '\r');
	TIM4_voidSetBusyWait(5000);
	GSM_voidSendCMD((u8*)"AT+CMGF=1", '\r');
	TIM4_voidSetBusyWait(5000);
}

void GSM_voidEnableSMSRx(void)
{
	GSM_voidSendCMD((u8*)"AT+CNMI=1,2,0,0,0", '\r');
	TIM4_voidSetBusyWait(5000);
}
void GSM_voidDisableSMSRx(void)
{
	GSM_voidSendCMD((u8*)"AT+CNMI=0,0,0,0,0", '\r');
	TIM4_voidSetBusyWait(5000);
}

void GSM_voidSendSMS(u8* Copy_u8ptrMessage)
{
	GSM_voidSendCMD((u8*)"AT+CMGS=\""PHONE_NUMBER"\"", '\r');
	TIM4_voidSetBusyWait(5000);
	GSM_voidSendCMD(Copy_u8ptrMessage, 0x1A);
	GSM_voidSendCMD((u8*)"\r", 0);
	TIM4_voidSetBusyWait(5000);
}

void GSM_voidMakeCall(void)
{
	GSM_voidSendCMD((u8*)"ATD + "PHONE_NUMBER";", '\r');
	TIM4_voidSetBusyWait(5000);
}

void GSM_voidSetSMSVerificationCallBack(void (*LpF)(void))
{
	GSM_GpF = LpF;
	USART1_voidSetCallBack(&GSM_voidCheckSMS);
	USART1_voidEnableRxINT();
}

static void GSM_voidSendCMD(u8* Copy_u8ptrMessage, u8 Copy_u8Confirmation)
{
	u16 Local_u16Length = 0;
	while(Local_u16Length != 0xFFFF)
	{
		if (Copy_u8ptrMessage[Local_u16Length] == '\0')
		{
			break;
		}
		Local_u16Length++;
	}
	for (u16 Local_u16Counter = 0; Local_u16Counter < Local_u16Length; Local_u16Counter++)
	{
		(void)USART1_u8Trancieve(Copy_u8ptrMessage[Local_u16Counter]);
	}
	if (Copy_u8Confirmation != 0)
	{
		(void)USART1_u8Trancieve(Copy_u8Confirmation);
	}
}

static void GSM_voidCheckSMS(void)
{
	static u8 Local_u8Counter = 0;
	if (Local_u8Counter == 1)
	{
		if (USART1_u8Receive() == 'C')
		{
			Local_u8Counter++;
		}
		else
		{
			Local_u8Counter = 0;
		}
	}
	else if (Local_u8Counter == 2)
	{
		if (USART1_u8Receive() == 'M')
		{
			Local_u8Counter++;
		}
		else
		{
			Local_u8Counter = 0;
		}
	}
	else if (Local_u8Counter == 3)
	{
		if (USART1_u8Receive() == 'T')
		{
			Local_u8Counter++;
		}
		else
		{
			Local_u8Counter = 0;
		}
	}
	else if (Local_u8Counter == 4)
	{
		if (USART1_u8Receive() == ':')
		{
			Local_u8Counter = 0;
			USART1_voidDisableRxINT();
			USART1_voidEnableRxDMA();
			DMA2_voidSetCallBack(&GSM_voidVerifySMS);
			DMA2_voidStart(S2, USART1_ADDR, (u32)&GSM_u8MessageBuffer, PN_STRLENGTH + 5);
		}
		else
		{
			Local_u8Counter = 0;
		}
	}
	else
	{
		if (USART1_u8Receive() == '+')
		{
			Local_u8Counter++;
		}
	}
}

static void GSM_voidVerifySMS(void)
{
	u8 Local_u8Counter;
	u8 Local_u8Index;
	for (Local_u8Counter = 0; Local_u8Counter < 4; Local_u8Counter++)
	{
		if (GSM_u8MessageBuffer[Local_u8Counter] == '"')
		{
			Local_u8Counter++;
			for (Local_u8Index = 0; Local_u8Index < PN_STRLENGTH; Local_u8Index++)
			{
				if (GSM_u8MessageBuffer[Local_u8Counter + Local_u8Index] != GSM_u8Phone_Number[Local_u8Index])
				{
					break;
				}
			}
			if (Local_u8Index == PN_STRLENGTH && GSM_u8MessageBuffer[Local_u8Counter + PN_STRLENGTH] == '"')
			{
				USART1_voidDisableRxDMA();
				if (GSM_GpF != NULL)
				{
					GSM_GpF();
				}
				return;
			}
		}
	}
	USART1_voidDisableRxDMA();
	USART1_voidEnableRxINT();
}
