/********************************************/
/* SWC: GSM Driver                          */
/********************************************/
#ifndef GSM_INTERFACE_H
#define GSM_INTERFACE_H

void GSM_voidInit(void);
void GSM_voidEnableSMSRx(void);
void GSM_voidDisableSMSRx(void);
void GSM_voidSendSMS(u8* Copy_u8ptrMessage);
void GSM_voidMakeCall(void);
u8 GSM_u8RecordMessage(void);
void GSM_voidSetSMSVerificationCallBack(void (*LpF)(void));

#endif
