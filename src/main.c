#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "STK_Interface.h"
#include "GPIO_Interface.h"
#include "NVIC_Interface.h"
#include "EXTI_Interface.h"
#include "IR_Interface.h"
#include "TIM2_Interface.h"

#define		UNLOCKREQ		0
#define		UNLOCKED		1
#define		ALERT			2
#define		ALERTACK		3
#define		ENGINEON		4
#define		BUTTONHOLD		5

u16 APP_u16Flags;
u32 APP_u32NextUnlockAttemptTime = 0;
u32 APP_u32NextIgnitionAttemptTime = 0;
u32 APP_u32LEDTurnOffTime = 0;
void APP_voidUnlockRequest(void);
void APP_voidTimerAdjust(void);

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
	/* Enable Clk for the peripheral TIM2 */
	RCC_voidEnablePerClk(APB1, 0);
    /* Init SysTick */
    STK_voidInit();
    /* Output push pull low speed pins */
    GPIO_voidSetPinMode(IOA, PIN1, OUTPUT);
	GPIO_voidSetPinType(IOA, PIN1, OUTPUT_PP);
	GPIO_voidSetPinSpeed(IOA, PIN1, OUTPUT_LS);
	GPIO_voidSetPinMode(IOA, PIN2, OUTPUT);
	GPIO_voidSetPinType(IOA, PIN2, OUTPUT_PP);
	GPIO_voidSetPinSpeed(IOA, PIN2, OUTPUT_LS);
	GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_HIGH);
	GPIO_voidSetPinMode(IOC, PIN13, OUTPUT);
	GPIO_voidSetPinType(IOC, PIN13, OUTPUT_PP);
	GPIO_voidSetPinSpeed(IOC, PIN13, OUTPUT_LS);
    /* Input pull up pin */
    GPIO_voidSetPinMode(IOA, PIN0, INPUT);
	GPIO_voidSetPinPuPdConfig(IOA, PIN0, INPUT_PU);
	/* IR Init */
	IR_voidInit(EXTI_PORTC, PIN14);
	IR_voidSetCallBack(&APP_voidUnlockRequest);
	/* Enable EXTI15_10 interrupt */
	NVIC_voidEnablePeriInt(40);
	/* TIM2 Init */
	TIM2_voidInit();
	TIM2_voidSetIntervalPeriodic(0xFFFFFFFF, &APP_voidTimerAdjust);
	/* Enable TIM2 interrupt */
	NVIC_voidEnablePeriInt(28);

    APP_u16Flags = 0;
    u8 Local_u8Attempts = 9;
    u32 Local_u32CurrTime;
    while(1)
    {
    	Local_u32CurrTime = TIM2_u32GetElapsedTime();
    	if (GET_BIT(APP_u16Flags, UNLOCKREQ) && Local_u32CurrTime >= APP_u32NextUnlockAttemptTime)
    	{
    		if (GET_BIT(APP_u16Flags, UNLOCKED))
    		{
    			if (IR_u8GetFrameData() == 0xE2)
        		{
        			CLR_BIT(APP_u16Flags, UNLOCKED);
        		}
    		}
    		else
    		{
    			if (IR_u8GetFrameData() == 0xA2)
        		{
        			/* If the received code is correct, unlock the car */
        			Local_u8Attempts = 9;
        			SET_BIT(APP_u16Flags, UNLOCKED);
        		}
    			else
    			{
    				/* Brute-forcing protection */
	    			if (Local_u8Attempts)
	    			{
	    				Local_u8Attempts--;
	    			}
	    			else
	    			{
	    				SET_BIT(APP_u16Flags, ALERT);
	    			}
    			}
    		}
    		GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_LOW);
    		APP_u32LEDTurnOffTime = Local_u32CurrTime + 250000;
    		APP_u32NextUnlockAttemptTime = Local_u32CurrTime + 1000000;
    	}
    	CLR_BIT(APP_u16Flags, UNLOCKREQ);
    	if (GET_BIT(APP_u16Flags, BUTTONHOLD) && GPIO_u8GetPinValue(IOA, PIN0))
    	{
    		CLR_BIT(APP_u16Flags, BUTTONHOLD);
    		APP_u32NextIgnitionAttemptTime = Local_u32CurrTime + 500000;
    	}
    	else if (!GPIO_u8GetPinValue(IOA, PIN0) && !GET_BIT(APP_u16Flags, ALERT) && !GET_BIT(APP_u16Flags, BUTTONHOLD) && Local_u32CurrTime >= APP_u32NextIgnitionAttemptTime)
    	{
    		if (GET_BIT(APP_u16Flags, UNLOCKED))
    		{
    			TOG_BIT(APP_u16Flags, ENGINEON);
    		}
    		else
    		{
    			SET_BIT(APP_u16Flags, ALERT);
    			CLR_BIT(APP_u16Flags, ENGINEON);
    		}
    		SET_BIT(APP_u16Flags, BUTTONHOLD);
    	}
    	if (GET_BIT(APP_u16Flags, ENGINEON))
    	{
    		/* Start the engine */
    		GPIO_voidSetPinValueDirectAccess(IOA, PIN2, OUTPUT_HIGH);
    	}
    	else
    	{
    		/* Shut down the engine */
    		GPIO_voidSetPinValueDirectAccess(IOA, PIN2, OUTPUT_LOW);
    	}
    	if (GET_BIT(APP_u16Flags, ALERT))
    	{
    		if (!GET_BIT(APP_u16Flags, ALERTACK))
    		{
	    		GPIO_voidSetPinValueDirectAccess(IOA, PIN1, OUTPUT_HIGH);
	    		SET_BIT(APP_u16Flags, ALERTACK);
    		}
    	}
    	if (APP_u32LEDTurnOffTime && Local_u32CurrTime >= APP_u32LEDTurnOffTime)
    	{
    		GPIO_voidSetPinValueDirectAccess(IOC, PIN13, OUTPUT_HIGH);
    		APP_u32LEDTurnOffTime = 0;
    	}
    }
}

void APP_voidUnlockRequest(void)
{
	if (!GET_BIT(APP_u16Flags, ALERT) && !GET_BIT(APP_u16Flags, ENGINEON))
	{
		/* Allow unlock request reception */
		SET_BIT(APP_u16Flags, UNLOCKREQ);
	}
}

void APP_voidTimerAdjust(void)
{
	/* Reset all cool-downs */
	APP_u32NextUnlockAttemptTime = 0;
	APP_u32NextIgnitionAttemptTime = 0;
	APP_u32LEDTurnOffTime = 0;
}
