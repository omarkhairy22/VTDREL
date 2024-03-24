/********************************************/
/* SWC: EXTI Driver                         */
/********************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

void EXTI_voidSetEXTILineEnable(u8 Copy_u8LineID);
void EXTI_voidSetEXTILineDisable(u8 Copy_u8LineID);
void EXTI_voidSetSenseControl(u8 Copy_u8SenseControl, u8 Copy_u8LineID);
void EXTI_voidSetEXTIPinConfig(u8 Copy_u8PortID, u8 Copy_u8LineID);
void EXTI_voidSetEXTISWI(u8 Copy_u8LineID);
void EXTI_voidSetCallBack(void (*LPF)(void));

#define FALLING_EDGE	0
#define RISING_EDGE	1
#define ON_CHANGE	2

#define EXTI_LINE0	0
#define EXTI_LINE1	1
#define EXTI_LINE2	2
#define EXTI_LINE3	3
#define EXTI_LINE4	4
#define EXTI_LINE5	5
#define EXTI_LINE6	6
#define EXTI_LINE7	7
#define EXTI_LINE8	8
#define EXTI_LINE9	9
#define EXTI_LINE10	10
#define EXTI_LINE11	11
#define EXTI_LINE12	12
#define EXTI_LINE13	13
#define EXTI_LINE14	14
#define EXTI_LINE15	15

#define EXTI_PORTA	0
#define EXTI_PORTB	1
#define EXTI_PORTC	2

#endif
