## Hardware Components
* STM32F401CCU6 Microcontroller
* SIM900 GSM Module
* VS1838B Infrared Receiver
* Simple NEC remote
* L293D motor driver
* Simple DC motor

## MCU PIN Configurations
| PIN  |             Function                |
|------|-------------------------------------|
|PINA0 | Engine ignition push button         |
|PINA1 | 'Alert' LED                         |
|PINA2 | Connected to driver 'Enable 1,2'    |
|PINA3 | Connected to driver 'Input 1'       |
|PINA9 | Connected to GSM module 'RXD'       |
|PINA10| Connected to GSM module 'TXD'       |
|PINC13| 'Unlock/Lock' LED                   |
|PINC14| Connected to IR receiver 'OUT'      |
