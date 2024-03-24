/********************************************/
/* SWC: STK Driver                          */
/********************************************/
/*File Guard*/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

#define STK_CTRL                    *((volatile u32*)0xE000E010)
#define STK_LOAD                    *((volatile u32*)0xE000E014)
#define STK_VAL                     *((volatile u32*)0xE000E018)
#define STK_CALIB                   *((volatile u32*)0xE000E01C)

#define AHB_DIV_BY_8                0
#define AHB                         1

#define SINGLE_INTERVAL_MODE        0
#define PERIODIC_INTERVAL_MODE      1


#endif
