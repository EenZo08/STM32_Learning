#ifndef __MYI2C_H__
#define __MYI2C_H__
#include "stm32f10x.h"
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
uint8_t MyI2C_RecvAck(void);
void MyI2C_SendAck(uint8_t ack);
void MyI2C_SendByte(uint8_t byte);
uint8_t MyI2C_RecvByte(void);

#endif // !1__MYI2C_H__