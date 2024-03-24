/********************************************/
/* SWC: GPIO Driver                         */
/********************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*GPIOA Base Address is 0x40020000*/
/*GPIOB Base Address is 0x40020400*/
/*GPIOC Base Address is 0x40020800*/

typedef struct 
{
    volatile u32 MODER;
    volatile u32 OTYPER;
    volatile u32 OSPEEDR;
    volatile u32 PUPDR;
    volatile u32 IDR;
    volatile u32 ODR;
    volatile u32 BSRR;
    volatile u32 LCKR;
    volatile u32 AFRL;
    volatile u32 AFRH;
}GPIO_t;

#define GPIOA            ((volatile GPIO_t*)0x40020000)
#define GPIOB            ((volatile GPIO_t*)0x40020400)
#define GPIOC            ((volatile GPIO_t*)0x40020800)


#endif
