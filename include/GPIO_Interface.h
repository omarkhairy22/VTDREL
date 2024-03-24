/********************************************/
/* SWC: GPIO Driver                         */
/********************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

void GPIO_voidSetPinMode(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Mode);
void GPIO_voidSetPinType(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Type);
void GPIO_voidSetPinSpeed(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Speed);
void GPIO_voidSetPinPuPdConfig(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PUPDType);
void GPIO_voidSetPinAltFuncNo(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8FuncNo);
void GPIO_voidSetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Value);
void GPIO_voidSetPinValueDirectAccess(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8SetRstType);
void GPIO_voidSetPortValue(u8 Copy_u8PortId, u32 Copy_u32Value);
u8   GPIO_u8GetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId);

#define IOA                 0
#define IOB                 1
#define IOC                 2

#define PIN0                0 
#define PIN1                1 
#define PIN2                2 
#define PIN3                3 
#define PIN4                4 
#define PIN5                5 
#define PIN6                6 
#define PIN7                7 
#define PIN8                8 
#define PIN9                9 
#define PIN10               10
#define PIN11               11
#define PIN12               12
#define PIN13               13
#define PIN14               14
#define PIN15               15
#define PIN16               16


#define INPUT               0
#define OUTPUT              1
#define AF                  2
#define ANALOG              3

#define OUTPUT_PP           0
#define OUTPUT_OD           1

#define OUTPUT_LS           0
#define OUTPUT_MS           1
#define OUTPUT_HS           2

#define OUTPUT_LOW          0
#define OUTPUT_HIGH         1

#define OUTPUT_RST          0
#define OUTPUT_SET          1

#define INPUT_FLOATING      0
#define INPUT_PU            1
#define INPUT_PD            2

#define AF0					0
#define AF1					1
#define AF2					2
#define AF3					3
#define AF4					4
#define AF5					5
#define AF6					6
#define AF7					7
#define AF8					8
#define AF9					9
#define AF10				10
#define AF11				11
#define AF12				12
#define AF13				13
#define AF14				14
#define AF15				15

#endif
