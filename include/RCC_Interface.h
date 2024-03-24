/********************************************/
/* SWC: RCC Driver                          */
/********************************************/
/*File Guard*/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

void RCC_voidInitSysClk(void);
void RCC_voidEnablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId);

#define AHB1            0
#define AHB2            1
#define APB1            2
#define APB2            3
#define AHB1LP          4
#define AHB2LP          5
#define APB1LP          6
#define APB2LP          7

#endif
