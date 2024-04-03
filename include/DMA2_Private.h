/********************************************/
/* SWC: DMA2 Driver                         */
/********************************************/
/*File Guard*/
#ifndef DMA2_PRIVATE_H
#define DMA2_PRIVATE_H

/*DMA2 : AHB1, Base Address: 0x40026400*/
#define DMA2_LISR				*((volatile u32*)0x40026400)
#define DMA2_HISR				*((volatile u32*)0x40026404)
#define DMA2_LIFCR				*((volatile u32*)0x40026408)
#define DMA2_HIFCR				*((volatile u32*)0x4002640C)


typedef struct
{
    volatile u32 SxCR;
    volatile u32 SxNDTR;
    volatile u32 SxPAR;
    volatile u32 SxM0AR;
    volatile u32 SxM1AR;
    volatile u32 SxFCR;
}DMA2Stream_t;

typedef struct
{
	volatile DMA2Stream_t Stream[8];
}DMA2_t;

#define DMA2            ((volatile DMA2_t*)(0x40026400 + 0x10))

#endif
