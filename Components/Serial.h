#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "stm32f10x.h"

extern uint8_t Serial_TXData[];//发送数据数组
extern uint8_t Serial_RXData[];//接收数据数组
extern char Serial_RXStr[];//接收文本数组
extern uint8_t Serial_RXFlag;//接收标志

void Serial_Init(void);
void Serial_SendByte(uint8_t data);
void Serial_SendString(char *str);
void Serial_SendNumber(uint32_t num, uint8_t len);
void Serial_SendHex(uint32_t num, uint8_t len);
void Serial_SendArray(uint8_t *arr, int len);
uint8_t Serial_GetRXFlag(void);
// uint8_t Serial_GetRXData(void);
void Serial_SendPacket(void);
#endif