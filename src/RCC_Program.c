/********************************************/
/* SWC: RCC Driver                          */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"

/*************************************/
/* Func. Name: RCC_voidInitSysClk    */
/* i/p arguments: nothing            */
/* o/p arguments: nothing            */
/* Desc. : This API allows user to   */ 
/*select the clk source of the system*/
/*************************************/
void RCC_voidInitSysClk(void)
{
    #if SYS_CLK_SRC == HSI
        /*1- Turn On HSI*/
        SET_BIT(RCC_CR, HSION);
        /*2- Select HSI as My System Clk*/
        CLR_BIT(RCC_CFGR, SW0);
        CLR_BIT(RCC_CFGR, SW1);
    #elif SYS_CLK_SRC == HSE
        /*1- Turn ON HSE*/
        SET_BIT(RCC_CR, HSEON);
        /*2- Select HSE as My Clk Src*/
        SET_BIT(RCC_CFGR, SW0);
        CLR_BIT(RCC_CFGR, SW1);
        /*3- Select Bypass Mode*/
        #if BYPASS_MODE == NOTPYBASSED
            CLR_BIT(RCC_CR, 18);
        #elif BYPASS_MODE == PYBASSED
            SET_BIT(RCC_CR, 18);
        #endif
    #elif SYS_CLK_SRC == PLL
        /*1- PLL Source*/
        #if PLL_SOURCE == HSI
            CLR_BIT(RCC_PLLCFGR, 22);
        #elif PLL_SOURCE == HSE
            SET_BIT(RCC_PLLCFGR, 22);
        #endif
        /*2- PLLM = 16*/
        CLR_BIT(RCC_PLLCFGR, 5);
        SET_BIT(RCC_PLLCFGR, 4);
        CLR_BIT(RCC_PLLCFGR, 3);
        CLR_BIT(RCC_PLLCFGR, 2);
        CLR_BIT(RCC_PLLCFGR, 1);
        CLR_BIT(RCC_PLLCFGR, 0);
        /*3- PLLN = 336*/
        SET_BIT(RCC_PLLCFGR, 14);
        CLR_BIT(RCC_PLLCFGR, 13);
        SET_BIT(RCC_PLLCFGR, 12);
        CLR_BIT(RCC_PLLCFGR, 11);
        SET_BIT(RCC_PLLCFGR, 10);
        CLR_BIT(RCC_PLLCFGR, 9);
        CLR_BIT(RCC_PLLCFGR, 8);
        CLR_BIT(RCC_PLLCFGR, 7);
        CLR_BIT(RCC_PLLCFGR, 6);
        /*4- PLLP = 4*/
        CLR_BIT(RCC_PLLCFGR, 17);
        SET_BIT(RCC_PLLCFGR, 16);
        /*5- Turn ON PLL*/
        SET_BIT(RCC_CR, PLLON);
        /*6- Select PLL as My Clk Src*/
        CLR_BIT(RCC_CFGR, SW0);
        SET_BIT(RCC_CFGR, SW1);
    #else   
        #warning "Invalid Configuration"
        
    #endif
    // Prescale AHB by 2
    SET_BIT(RCC_CFGR, 7);
    CLR_BIT(RCC_CFGR, 6);
    CLR_BIT(RCC_CFGR, 5);
    CLR_BIT(RCC_CFGR, 4);
}

/*****************************************************************/
/* Func. Name: RCC_voidEnablePerClk                              */
/* i/p arguments: Copy_u8BusId: AHB1, AHB2, APB1, APB2           */
/* i/p arguments: Copy_u8PerId: 0 --> 31                         */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to Enable clk for a specific per.*/
/*****************************************************************/
void RCC_voidEnablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId) //RCC_voidEnablePerClk(AHB2, 21);
{
    /*i/p validation*/
    if((Copy_u8BusId > APB2) || (Copy_u8PerId > 31))
    {
        /*Do Nothing*/
    }
    else
    {
        switch(Copy_u8BusId)
        {
            case AHB1:  SET_BIT(RCC_AHB1ENR, Copy_u8PerId);
                        break;
            case AHB2:  if(Copy_u8PerId != 7)
                        {
                            /*Do Nothing*/
                        }
                        else
                        {
                            SET_BIT(RCC_AHB2ENR, Copy_u8PerId);
                        }
                        break;
            case APB1:  SET_BIT(RCC_APB1ENR, Copy_u8PerId);
                        break;
            case APB2:  SET_BIT(RCC_APB2ENR, Copy_u8PerId);
                        break;
            case AHB1LP:SET_BIT(RCC_AHB1LPENR, Copy_u8PerId);
                        break;
            case AHB2LP:if(Copy_u8PerId != 7)
                        {
                            /*Do Nothing*/
                        }
                        else
                        {
                            SET_BIT(RCC_AHB2LPENR, Copy_u8PerId);
                        }
                        break;
            case APB1LP:SET_BIT(RCC_APB1LPENR, Copy_u8PerId);
                        break;
            case APB2LP:SET_BIT(RCC_APB2LPENR, Copy_u8PerId);
                        break;
        }
    }
}

/******************************************************************/
/* Func. Name: RCC_voidEnablePerClk                               */
/* i/p arguments: Copy_u8BusId: AHB1, AHB2, APB1, APB2            */
/* i/p arguments: Copy_u8PerId: 0 --> 31                          */
/* o/p arguments: nothing                                         */
/* Desc. : This API allows user to Disable clk for a specific per.*/
/******************************************************************/
void RCC_voidDisablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    /*i/p validation*/
    if((Copy_u8BusId > APB2) || (Copy_u8PerId > 31))
    {
        /*Do Nothing*/
    }
    else
    {
        switch(Copy_u8BusId)
        {
            case AHB1:  CLR_BIT(RCC_AHB1ENR, Copy_u8PerId);
                        break;
            case AHB2:  if(Copy_u8PerId != 7)
                        {
                            /*Do Nothing*/
                        }
                        else
                        {
                            CLR_BIT(RCC_AHB2ENR, Copy_u8PerId);
                        }
                        break;
            case APB1:  CLR_BIT(RCC_APB1ENR, Copy_u8PerId);
                        break;
            case APB2:  CLR_BIT(RCC_APB2ENR, Copy_u8PerId);
                        break;
            case AHB1LP:CLR_BIT(RCC_AHB1LPENR, Copy_u8PerId);
                        break;
            case AHB2LP:if(Copy_u8PerId != 7)
                        {
                            /*Do Nothing*/
                        }
                        else
                        {
                            CLR_BIT(RCC_AHB2LPENR, Copy_u8PerId);
                        }
                        break;
            case APB1LP:CLR_BIT(RCC_APB1LPENR, Copy_u8PerId);
                        break;
            case APB2LP:CLR_BIT(RCC_APB2LPENR, Copy_u8PerId);
                        break;
        }
    }
}
