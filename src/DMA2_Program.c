/********************************************/
/* SWC: DMA2 Driver                         */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DMA2_Interface.h"
#include "DMA2_Private.h"
#include "DMA2_Config.h"

/*Global Pointer to Function*/
void (*DMA2_GPF)(void) = NULL;

void DMA2_voidChannelInit(u8 Copy_u8Stream, u8 Copy_u8Channel, u8 Copy_u8Direction)
{
	if (Copy_u8Stream > S7 || Copy_u8Channel > CH7 || Copy_u8Direction > MTM)
	{
		/*Do nothing*/
	}
	else
	{
		// Clear EN bit
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 0);
		// Enable DMA2 interrupt
		SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 4);
		// DMA2 is the flow controller
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 5);
		switch(Copy_u8Direction)
		{
		case PTM:
			// Peripheral-to-memory
			CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 6);
			CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 7);
			// PINC OFF
			CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 9);
			// MINC ON
			SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 10);
			break;
		case MTP:
			// Memory-to-peripheral
			SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 6);
			CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 7);
			// PINC ON
			SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 9);
			// MINC OFF
			CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 10);
			break;
		default:
			// Memory-to-memory
			CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 6);
			SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 7);
			// PINC ON
			SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 9);
			// MINC ON
			SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 10);
		}
		// Transfer byte by byte (8-bit)
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 11);
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 12);
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 13);
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 14);
		// Select channel
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 25);
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 26);
		CLR_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 27);
		DMA2->Stream[Copy_u8Stream].SxCR |= Copy_u8Channel << 25;
	}
}

void DMA2_voidStart(u8 Copy_u8Stream, u32 Copy_u32Source, u32 Copy_u32Destination, u16 Copy_u16NumberOfItems)
{
	if (Copy_u8Stream > S7)
	{
		/*Do nothing*/
	}
	else
	{
		// Prepare transmission
		DMA2->Stream[Copy_u8Stream].SxPAR = Copy_u32Source;
		DMA2->Stream[Copy_u8Stream].SxM0AR = Copy_u32Destination;
		DMA2->Stream[Copy_u8Stream].SxNDTR = Copy_u16NumberOfItems;
		// Enable EN bit
		SET_BIT(DMA2->Stream[Copy_u8Stream].SxCR, 0);
	}
}

void DMA2_voidSetCallBack(void (*LPF)(void))
{
	DMA2_GPF = LPF;
}

void DMA2_Stream0_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 5);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream1_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 11);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream2_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 21);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream3_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 27);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream4_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 5);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream5_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 11);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream6_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 21);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}

void DMA2_Stream7_IRQHandler()
{
	SET_BIT(DMA2_LIFCR, 27);
	if (DMA2_GPF != NULL)
	{
		DMA2_GPF();
	}
}
