#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "STK_Interface.h"
#include "GPIO_Interface.h"
#include "NVIC_Interface.h"
#include "EXTI_Interface.h"
#include "USART1_Interface.h"
#include "DMA2_Interface.h"
#include "TIM3_Interface.h"
#include "TIM4_Interface.h"
#include "IR_Interface.h"
#include "GSM_Interface.h"

#define		IRCODE			0xA2

#define		UNLOCKREQ		0
#define		UNLOCKED		1
#define		LEDON			2
#define		ALERT			3
#define		ALERTACK		4
#define		LOCTRACKING		5
#define		SMSRXFLAG		6
#define		ADVLOCKFLAG		7
#define		BUTTONHOLD		8
#define		ENGINEON		9

u8 APP_u8Attempts;
u16 APP_u16Flags;
u32 APP_u32NextUnlockAttemptTime = 0;
u32 APP_u32NextIgnitionAttemptTime = 0;
u32 APP_u32LEDTurnOffTime = 0;
u32 APP_u32LocUpdateTime = 0;
void APP_voidUnlockRequest(void);
void APP_voidTimerAdjust(void);
void APP_voidUserVerified(void);

int main()
{
    /* Init system clock */
    RCC_voidInitSysClk();
    /* Enable clock for the peripheral GPIOA */
    RCC_voidEnablePerClk(AHB1, 0);
    /* Enable clock for the peripheral GPIOC */
    RCC_voidEnablePerClk(AHB1, 2);
    /* Enable Clk for the peripheral SYSCFG */
    RCC_voidEnablePerClk(APB2, 14);
    /* Enable Clk for the peripheral USART1 */
    RCC_voidEnablePerClk(APB2, 4);
    /* Enable Clk for the peripheral DMA2 */
    RCC_voidEnablePerClk(AHB1, 22);
    /* Enable Clk for the peripheral TIM3 */
    RCC_voidEnablePerClk(APB1, 1);
    /* Enable Clk for the peripheral TIM4 */
    RCC_voidEnablePerClk(APB1, 2);
    /* Init SysTick */
    STK_voidInit();
    STK_voidSetIntervalPeriodic(0xFFFFFFFF, &APP_voidTimerAdjust);
    /* Output push pull low speed pins */
    GPIO_voidSetPinMode(IOA, PIN1, OUTPUT);
    GPIO_voidSetPinType(IOA, PIN1, OUTPUT_PP);
    GPIO_voidSetPinSpeed(IOA, PIN1, OUTPUT_LS);
    GPIO_voidSetPinMode(IOA, PIN2, OUTPUT);
    GPIO_voidSetPinType(IOA, PIN2, OUTPUT_PP);
    GPIO_voidSetPinSpeed(IOA, PIN2, OUTPUT_LS);
    GPIO_voidSetPinMode(IOA, PIN3, OUTPUT);
    GPIO_voidSetPinType(IOA, PIN3, OUTPUT_PP);
    GPIO_voidSetPinSpeed(IOA, PIN3, OUTPUT_LS);
    GPIO_voidSetPinValueDirectAccess(IOA, PIN3, OUTPUT_HIGH);
    GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_HIGH);
    GPIO_voidSetPinMode(IOC, PIN13, OUTPUT);
    GPIO_voidSetPinType(IOC, PIN13, OUTPUT_PP);
    GPIO_voidSetPinSpeed(IOC, PIN13, OUTPUT_LS);
    /* Input pull up pin */
    GPIO_voidSetPinMode(IOA, PIN0, INPUT);
    GPIO_voidSetPinPuPdConfig(IOA, PIN0, INPUT_PU);
    /* USART1 pins */
    GPIO_voidSetPinMode(IOA, PIN9, AF);
    GPIO_voidSetPinAltFuncNo(IOA, PIN9, AF7);
    GPIO_voidSetPinMode(IOA, PIN10, AF);
    GPIO_voidSetPinAltFuncNo(IOA, PIN10, AF7);
    /* USART1 Init */
    USART1_voidInit();
    /* DMA2 Init */
    DMA2_voidChannelInit(S2, CH4, PTM);
    /* TIM3 Init */
    TIM3_voidInit();
    /* TIM4 Init */
    TIM4_voidInit();
    /* Enable USART1 interrupt */
    NVIC_voidEnablePeriInt(37);
    /* Enable DMA2_Stream2 interrupt */
    NVIC_voidEnablePeriInt(58);
    /* Enable TIM3 interrupt */
    NVIC_voidEnablePeriInt(29);
    /* Enable EXTI15_10 interrupt */
    NVIC_voidEnablePeriInt(40);
    /* IR Init */
    IR_voidInit(EXTI_PORTC, PIN14);
    IR_voidSetCallBack(&APP_voidUnlockRequest);
    /* GSM Init */
    GSM_voidInit();
    GSM_voidDisableSMSRx();

    APP_u8Attempts = 2;
    APP_u16Flags = 0;
    u32 Local_u32CurrTime;
    while(1)
    {
    	/* Check for the owner's response */
    	if (GET_BIT(APP_u16Flags, SMSRXFLAG))
    	{
    		if (GSM_u8RecordMessage())
    		{
    			/* Exit 'Alert' mode */
	    		GSM_voidDisableSMSRx();
	    		CLR_BIT(APP_u16Flags, ALERTACK);
	    		CLR_BIT(APP_u16Flags, ALERT);
	    		CLR_BIT(APP_u16Flags, LOCTRACKING);
	    		CLR_BIT(APP_u16Flags, ADVLOCKFLAG);
	    		GPIO_voidSetPinValueDirectAccess(IOA, PIN1, OUTPUT_LOW);
	    		GPIO_voidSetPinValueDirectAccess(IOA, PIN3, OUTPUT_HIGH);
	    		APP_u8Attempts = 2;
	    		GSM_voidSendSMS((u8*)"Car alert mode disabled!");
    		}
    		else if (!GET_BIT(APP_u16Flags, ADVLOCKFLAG))
    		{
    			/* Block engine driver */
    			GPIO_voidSetPinValueDirectAccess(IOA, PIN3, OUTPUT_LOW);
    			GSM_voidSetSMSVerificationCallBack(&APP_voidUserVerified);
    			GSM_voidSendSMS((u8*)"Advanced engine locking activated!");
    			SET_BIT(APP_u16Flags, ADVLOCKFLAG);
    		}
    		CLR_BIT(APP_u16Flags, SMSRXFLAG);
    	}
    	/* Record time since boot */
    	Local_u32CurrTime = STK_u32GetElapsedTime();
    	/* Turn off the unlock LED after a cool-down */
    	if (GET_BIT(APP_u16Flags, LEDON) && Local_u32CurrTime >= APP_u32LEDTurnOffTime)
    	{
    		GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_HIGH);
    		APP_u32LEDTurnOffTime = 0;
    		CLR_BIT(APP_u16Flags, LEDON);
    	}
    	/* Check for IR unlock requests */
    	if (GET_BIT(APP_u16Flags, UNLOCKREQ) && Local_u32CurrTime >= APP_u32NextUnlockAttemptTime)
    	{
    		if (GET_BIT(APP_u16Flags, UNLOCKED))
    		{
    			if (IR_u8GetFrameData() == IRCODE)
        		{
        			CLR_BIT(APP_u16Flags, UNLOCKED);
        			APP_u32LEDTurnOffTime = Local_u32CurrTime + 750000;
        			GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_LOW);
        			SET_BIT(APP_u16Flags, LEDON);
        		}
    		}
    		else
    		{
    			if (IR_u8GetFrameData() == IRCODE)
        		{
        			/* If the received code is correct, unlock the car */
    				APP_u8Attempts = 2;
        			SET_BIT(APP_u16Flags, UNLOCKED);
        			APP_u32LEDTurnOffTime = Local_u32CurrTime + 300000;
        			GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_LOW);
        			SET_BIT(APP_u16Flags, LEDON);
        		}
    			else if (APP_u8Attempts)
    			{
    				APP_u8Attempts--;
    			}
    			else
    			{
    				SET_BIT(APP_u16Flags, ALERT);
    			}
    		}
    		APP_u32NextUnlockAttemptTime = Local_u32CurrTime + 750000;
    	}
    	/* Close processed/refused unlock request */
    	CLR_BIT(APP_u16Flags, UNLOCKREQ);
    	/* Check for ignition attempts */
    	if (GET_BIT(APP_u16Flags, BUTTONHOLD) && GPIO_u8GetPinValue(IOA, PIN0))
    	{
    		CLR_BIT(APP_u16Flags, BUTTONHOLD);
    		APP_u32NextIgnitionAttemptTime = Local_u32CurrTime + 500000;
    	}
    	else if (!GPIO_u8GetPinValue(IOA, PIN0) && !GET_BIT(APP_u16Flags, ALERT) && !GET_BIT(APP_u16Flags, BUTTONHOLD) && Local_u32CurrTime >= APP_u32NextIgnitionAttemptTime)
    	{
    		if (GET_BIT(APP_u16Flags, UNLOCKED))
    		{
    			/* Start/shut down the engine */
    			TOG_BIT(APP_u16Flags, ENGINEON);
    			GPIO_voidSetPinValueDirectAccess(IOA, PIN2, GET_BIT(APP_u16Flags, ENGINEON));
    		}
    		else if (APP_u8Attempts)
    		{
    			APP_u8Attempts--;
    		}
    		else
    		{
    			SET_BIT(APP_u16Flags, ALERT);
    		}
    		SET_BIT(APP_u16Flags, BUTTONHOLD);
    	}
    	/* Send current location */
    	if (GET_BIT(APP_u16Flags, LOCTRACKING) && Local_u32CurrTime >= APP_u32LocUpdateTime)
    	{
    		GSM_voidSendSMS((u8*)"<placeholder>");
    		APP_u32LocUpdateTime = Local_u32CurrTime + 3000000;
    	}
    	/* Notify the owner of a theft attempt if alert mode was activated */
    	if (GET_BIT(APP_u16Flags, ALERT))
    	{
    		if (!GET_BIT(APP_u16Flags, ALERTACK))
    		{
	    		GPIO_voidSetPinValueDirectAccess(IOA, PIN1, OUTPUT_HIGH);
	    		GSM_voidEnableSMSRx();
	    		GSM_voidMakeCall();
	    		GSM_voidSetSMSVerificationCallBack(&APP_voidUserVerified);
	    		SET_BIT(APP_u16Flags, ALERTACK);
	    		SET_BIT(APP_u16Flags, LOCTRACKING);
	    		APP_u32LocUpdateTime = Local_u32CurrTime + 3000000;
    		}
    	}
    }
}

void APP_voidUnlockRequest(void)
{
	if (!GET_BIT(APP_u16Flags, ALERT) && !GET_BIT(APP_u16Flags, ENGINEON))
	{
		/* Send unlock request */
		SET_BIT(APP_u16Flags, UNLOCKREQ);
	}
}

void APP_voidTimerAdjust(void)
{
	/* Reset all cool-downs */
	APP_u32NextUnlockAttemptTime = 0;
	APP_u32NextIgnitionAttemptTime = 0;
	APP_u32LEDTurnOffTime = 0;
	APP_u32LocUpdateTime = 0;
}

void APP_voidUserVerified(void)
{
	if (GET_BIT(APP_u16Flags, ALERT))
	{
		SET_BIT(APP_u16Flags, SMSRXFLAG);
	}
}
