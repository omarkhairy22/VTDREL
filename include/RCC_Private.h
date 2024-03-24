/********************************************/
/* SWC: RCC Driver                          */
/********************************************/
/*File Guard*/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*RCC : AHB1, Base Address: 0x40023800*/
#define RCC_CR                   *((volatile u32*)0x40023800)
#define RCC_PLLCFGR              *((volatile u32*)0x40023804)
#define RCC_CFGR                 *((volatile u32*)0x40023808)
#define RCC_AHB1ENR              *((volatile u32*)0x40023830)
#define RCC_AHB2ENR              *((volatile u32*)0x40023834)
#define RCC_APB1ENR              *((volatile u32*)0x40023840)
#define RCC_APB2ENR              *((volatile u32*)0x40023844)
#define RCC_AHB1LPENR            *((volatile u32*)0x40023850)
#define RCC_AHB2LPENR            *((volatile u32*)0x40023854)
#define RCC_APB1LPENR            *((volatile u32*)0x40023860)
#define RCC_APB2LPENR            *((volatile u32*)0x40023864)


/*Private Macros*/
#define HSI                      0
#define HSE                      1
#define PLL                      2

/*Bits Configuration*/
#define HSION                    0
#define SW0                      0
#define SW1                      1
#define HSEON                    16
#define PLLON					 24

#define NOTPYBASSED              0
#define BYPASSED                 1

#endif
