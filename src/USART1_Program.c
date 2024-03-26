/********************************************/
/* SWC: USART1 Driver                       */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART1_Interface.h"
#include "USART1_Private.h"
#include "USART1_Config.h"

/*Global Pointer to Function*/
void (*USART1_GpF)(void) = NULL;

void USART1_voidInit(void)
{
	// Enable Receiving and Transmitting
	SET_BIT(USART1_CR1, 2);
	SET_BIT(USART1_CR1, 3);
	// Disable CK pin
	CLR_BIT(USART1_CR2, 11);
	// Stop bit = 1 bit
	CLR_BIT(USART1_CR2, 12);
	CLR_BIT(USART1_CR2, 13);
	// Oversampling by 16
	CLR_BIT(USART1_CR1, 15);
	// Set baud rate = 9600
	USART1_BRR = 0x341;
	// Enable USART1
	SET_BIT(USART1_CR1, 13);
}

void USART1_voidTransmit(u8 Copy_u8Data)
{
	USART1_DR = Copy_u8Data;
	while(!GET_BIT(USART1_SR, 6));
}

u8 USART1_u8Receive(void)
{
	while(!GET_BIT(USART1_SR, 5));
	return USART1_DR;
}

u8 USART1_u8Trancieve(u8 Copy_u8Data)
{
	USART1_DR = Copy_u8Data;
	while(!GET_BIT(USART1_SR, 5) || !GET_BIT(USART1_SR, 6));
	return USART1_DR;
}

void USART1_voidEnableRxINT(void (*LpF)(void))
{
	// Save CallBack
	USART1_GpF = LpF;
    // Enable RXNE INT
	SET_BIT(USART1_CR1, 5);
}

void USART1_voidDisableRxINT(void)
{
	// Reset CallBack
	USART1_GpF = NULL;
	// Disable RXNE INT
	CLR_BIT(USART1_CR1, 5);
}

void USART1_IRQHandler()
{
	if (USART1_GpF != NULL)
	{
		USART1_GpF();
	}
}
