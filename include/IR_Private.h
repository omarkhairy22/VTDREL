/********************************************/
/* SWC: IR Driver                           */
/********************************************/
#ifndef IR_PRIVATE_H
#define IR_PRIVATE_H

static u8 IR_u8StartFlag = 0;
static u8 IR_u8Address;
static u8 IR_u8Data;
static u32 IR_u32Temp;

static void IR_voidRecord(void);
static void IR_voidEnd(void);

#endif
