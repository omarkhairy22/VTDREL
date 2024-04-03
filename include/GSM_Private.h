/********************************************/
/* SWC: GSM Driver                          */
/********************************************/
#ifndef GSM_PRIVATE_H
#define GSM_PRIVATE_H

static const u8 GSM_u8Phone_Number[] = PHONE_NUMBER;

static void GSM_voidSendCMD(u8* Copy_u8ptrMessage, u8 Copy_u8Confirmation);
static void GSM_voidCheckSMS(void);
static void GSM_voidVerifySMS(void);

#endif
