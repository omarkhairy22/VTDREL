# Vehicle Theft Detection with Remote Engine Locking
## Summary
The vehicle has two states: locked & unlocked, locking/unlocking the security system can be done from the IR remote. If the user entered three consecutive wrong IR codes attempts, the vehicle enters the 'Alert' mode, and attempting to start the engine while it's locked also activates that mode. While the vehicle is in 'Alert' mode, the engine cannot be started and the IR receiver doesn't respond to any new commands. The only way to exit that mode is sending an SMS of a special 6-character code from the owner's phone number, however, sending any other message from the owner's number will activate a secondary engine locking attempt; makes the 2 terminals on the motor grounded. The vehicle cannot be locked by the IR remote while the engine is running.
## Hardware Components
* STM32F401CCU6 Microcontroller
* SIM900 GSM Module
* VS1838B Infrared Receiver
* Simple NEC remote
* L293D motor driver
* Simple DC motor
## PIN Configurations
| PIN  |              Function                 |
|------|---------------------------------------|
|PINA0 | Engine ignition push button           |
|PINA1 | 'Alert' LED                           |
|PINA2 | Connected to motor driver 'Enable 1,2'|
|PINA3 | Connected to motor driver 'Input 1'   |
|PINA9 | Connected to GSM module 'RXD'         |
|PINA10| Connected to GSM module 'TXD'         |
|PINC13| 'Unlock/Lock' LED                     |
|PINC14| Connected to IR receiver 'OUT'        |
